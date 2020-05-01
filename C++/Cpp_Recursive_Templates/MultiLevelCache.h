#pragma once
#include <vector>
#include <type_traits>
#include <optional>
#include <iostream>

/*
Interface to model the generic memory operations.
*/
template <typename Key, typename Value>
struct MemoryInterface
{
	// fetches the data from the memory identifed by the key.
	// parameters: key to identify the memory location for the data.
	// returns: data, if the key is found otherwise nullopt (std::optional<Value>).
	virtual std::optional<Value> fetch(const Key& key)
	{
		return std::nullopt;
	}

	// stores the data in the memory identifed by the key.
	// parameters: key to identify the memory location to store the data.
	// returns: true, if store is successful otherwise false.
	virtual bool store(const Key& key, const Value& data, bool setdirty = true)
	{
		return false;
	}

	// returns true if data is dirty.
	virtual bool isDirty(const Key&) { return false; }

	virtual ~MemoryInterface() {}
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Multi Level Cache : Heirarchy implemented using Recursive Variadic Template
// Template arguments:
//                      Key - Type of Key to identify the data in the caches
//                      Value - Type of the data stored in the caches
//                      Cache - template template argument that defines CacheMemory of this
//                              derived class in the heirarchy. Cache closest to the 
//                              consumer (smallest cache) will be member of the most derived class
//                              of the instantiation.
//                      HigherLevelCaches... - variadic template argument list(ordered) that defines caches for
//                                             up the heirarchy. (recursively expanded.)
//////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key,
	typename Value,
	template <class, class, class, int> class Cache,
	template <class, class, class, int> class... HigherLevelCaches>
struct MultiLevelCache : protected MultiLevelCache<Key, Value, HigherLevelCaches...>
{
	// Parent Cache Type in the memory heirarchy.
	using HigherLevelMemory = typename MultiLevelCache<Key, Value, HigherLevelCaches...>::MemoryObject;

	// numeric level of this cache in the memory heirarchy. Used for logging purpose.
	// Higher the number, closer to the consumer in the heirachy.
	// Lower the number, closer to the soure(main) memory in the heirarchy.
	// Main memory will be at level 0 and the cache closest to the consumer will be at highest level.
	constexpr static const int level = MultiLevelCache<Key, Value, HigherLevelCaches...>::level + 1;

	// cache implementation of this memory heirarchy 
	using MemoryObject = Cache<Key, Value, HigherLevelMemory, level>;
	// cache memory instantiation as member of this class. (value semantics.)
	MemoryObject memory;

	// Constructor: Reference to the parent cache in the memory heirarchy is passed to this cache.
	//              In the event of cache miss, the data will be fetched from the parent cache 
	//              up in the heirarchy.
	//              Reference to the parent cache is always valid, since the parent cache object
	//              lives in the immediate base object. The immediate base object is valid
	//              as long as this derived class object lives.
	MultiLevelCache() : memory(MultiLevelCache<Key, Value, HigherLevelCaches...>::memory)
	{

	}

	// fetches data from the cache at the current heirarchy identified by the key 
	std::optional<Value> fetch(const Key& key)
	{
		return memory.fetch(key);
	}

	// stores data in the cache at current heirarchy.
	bool store(const Key& key, Value data)
	{
		return memory.store(key, data);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////
// Multi Level Cache : Base case for the recursive variadic template expansion
// Defines Top Level Main (source) Memory in the memory heirarchy (most base class).
// Numeric level of the main memory will be zero.
// Template arguments:
//                      Key - Type of Key to identify the data in the source memory
//                      Value - Type of the data stored in the source memory
//                      Cache - template template argument that defines top level (level 0) main memory of the 
//                              memory herirarchy.
//////////////////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, template <class, class, class, int> class SourceMemory>
struct MultiLevelCache<Key, Value, SourceMemory>
{
	// Source (Main) Memory is at the most base class in recursive instantiations.
	// Level of the main memory is identified as 0.
	constexpr static const int level = 0;

	// Main memory instatiation as member of this base class.
	using MemoryObject = SourceMemory<Key, Value, MemoryInterface<Key, Value>, 0>;
	MemoryObject memory;

	// Fetches data from the source memory.
	std::optional<Value> fetch(const Key& key)
	{
		return memory.fetch(key);
	}

	// stores data from the source memory.
	// returns true if successful.
	bool store(const Key& key, Value data)
	{
		return memory.store(key, data);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////

template<class T> struct dependent_false : std::false_type {};

//////////////////////////////////////////////////////////////////////////////////////////////
// CacheMemory : This template class implements the CacheMemory functionalities.
// Implements the MemoryInterface functions fetch, store and isDirty
// and satisfies the requirements for write-back store and cache miss handling.
// Template arguments:
//                      Key - Type of Key to identify the data in the cache memory.
//                      Value - Type of the data stored in the cache memory.
//                              both Key and Value should implement operator ==() and operator !=()
//                      HigherLevelMemory - Parent Cache up in the memory heirarchy.
//                      cachelevel - level of this cache in the memory herirarchy.
//                                   Lower the number, closer to the main memory.
//                                   level 1 cache is closest to the source and level max farthest.
//                      cache_size - compile time value to define the cache size.
//////////////////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value, typename HigherLevelMemory, int cachelevel, int cache_size>
struct CacheMemory : MemoryInterface<Key, Value>
{
private:

	// Compile time value to identify the level of the cache in the heirarchy.
	enum CacheLevel
	{
		LEVEL = cachelevel
	};

	enum class CacheValidity
	{
		INVALID, // cache entry will be invalid initially
		VALID,   // data is valid, in sync with main source. 
		DIRTY    // data has been modified.
	};

	// Cache Entry info
	struct CacheEntry
	{
		Key key;
		Value data;
		// Validity of the cache entry.
		CacheValidity validity = CacheValidity::INVALID;
	};

	// Function computes hash function from the given key and returns index into the cache.
	auto getIndex(const Key& key)
	{
		if constexpr (std::is_arithmetic_v<Key>)
		{
			return static_cast<unsigned long>(key) % cache_size;
		}
		else if constexpr (std::is_same_v<Key, std::string>)
		{
			// djb2 hash function algorithm.
			unsigned long hash = 5381;
			for (auto ch : key)
			{
				hash = (hash << 5) + hash + ch; /* hash * 33 + c */
			}
			return hash % cache_size;
		}
		else
		{
			static_assert(dependent_false<Key>::value,
				"CacheMemory::hashIndex: Key type should be either string or arithmetic");
		}
	}

	// vector of cache entries to store cache information.
	// vector size is of the given compile time cache size. 
	std::vector<CacheEntry> cache_entries = std::vector<CacheEntry>(cache_size);

	// Reference to the parent cache up in the memory heirarchy.
	HigherLevelMemory& higher_level_memory_reference;

public:
	CacheMemory(HigherLevelMemory & pp) : higher_level_memory_reference(pp)
	{

	}

	// Destructor:
	// This is a write-back cache and will have dirty cache entries for the modified data.
	// Dirty data to be written back to the parent cache, before this cache is destroyed.
	~CacheMemory()
	{
		for (const auto& e : cache_entries)
		{
			if (e.validity == CacheValidity::DIRTY)
			{
				higher_level_memory_reference.store(e.key, e.data, true);
			}
		}
	}

	// returns true if the data is modified in the cache and yet to be written back.
	bool isDirty(const Key & key)
	{
		auto index = getIndex(key);
		return (cache_entries[index].validity == CacheValidity::DIRTY);
	}

	// Implements the fetch interface with cache miss handling
	// Returns the data from the cache if it exists.
	// If there is a cache miss, try to get the data from the parent memory
	// and returns the data after storing it in the cache for further lookups. 
	std::optional<Value> fetch(const Key & key)
	{
		auto index = getIndex(key);
		if (cache_entries[index].validity != CacheValidity::INVALID && cache_entries[index].key == key)
		{
			// Data found at cache
			std::cout << ">>> fetch::" << "CacheLevel::" << LEVEL << " data for key " << key << " found at cache." << std::endl;
			return cache_entries[index].data;
		}

		// Cache Miss Handling:
		// Get the data from memory in higher heirarchy.
		std::cout << ">>> fetch::" << "CacheLevel::" << LEVEL << " data for key " << key << " missed at cache. trying higher level source..." << std::endl;
		auto data_from_higher_memory = higher_level_memory_reference.fetch(key);

		if (data_from_higher_memory.has_value())
		{
			std::cout << ">>> fetch::" << "CacheLevel::" << LEVEL << " data for key " << key << " found at higher level source..." << std::endl;
			// Store a local copy for further look ups.
			store(key, data_from_higher_memory.value(), higher_level_memory_reference.isDirty(key));
		}

		return data_from_higher_memory;
	}

	// Implements the store interface of the MemoryInterface.
	// Implements the write back cache functionality.
	// If setdirty is set to true, it means the value is dirty (modified) from the source.
	// Returns true if store is successful
	bool store(const Key & key, const Value & value, bool setdirty = true)
	{
		auto index = getIndex(key);

		auto existing_value = cache_entries[index];
		bool evicted = false;
		if (cache_entries[index].validity == CacheValidity::INVALID)
		{
			// data is dirty if it is dirty from the source.
			cache_entries[index].validity = (setdirty) ? CacheValidity::DIRTY : CacheValidity::VALID;
		}
		else if (cache_entries[index].key == key && cache_entries[index].data != value)
		{
			// if the value is modified for the same data identified by key, mark it as dirty.
			cache_entries[index].validity = CacheValidity::DIRTY;
		}
		else if (cache_entries[index].key != key)
		{
			// cache has already data at the same index. 
			// The existing data needs to be evicted to make way for the new data.
			evicted = true;
			cache_entries[index].validity = (setdirty) ? CacheValidity::DIRTY : CacheValidity::VALID;
		}

		cache_entries[index].key = key;
		cache_entries[index].data = value;

		bool retvalue = true;
		if (evicted)
		{
			// If the exising data in the cache is evicted, propagate it to the memory at the 
			// next higher level.
			std::cout << "<<< store::" << "CacheLevel::" << LEVEL << " data for key " << existing_value.key << " evicted to higher memory";
			std::cout << " as " << ((existing_value.validity == CacheValidity::DIRTY) ? "dirty" : "valid");
			std::cout << " to store new key : " << key << std::endl;
			retvalue = higher_level_memory_reference.store(existing_value.key, existing_value.data, (existing_value.validity == CacheValidity::DIRTY));
		}

		if (retvalue)
		{
			std::cout << "<<< store::" << "CacheLevel::" << LEVEL << " data for key " << key << " stored at cache";
			std::cout << " as " << ((cache_entries[index].validity == CacheValidity::DIRTY) ? "dirty" : "valid.") << std::endl;
		}

		return retvalue;
	}
};