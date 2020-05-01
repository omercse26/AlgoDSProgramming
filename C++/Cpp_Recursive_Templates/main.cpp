#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <experimental/filesystem>

#include "MultiLevelCache.h"

namespace fs = std::experimental::filesystem;

//////////////////////////////////////////////////////////////////////////////////////////////
// FileDataSource : This template class implements the Main Data Source functionalities.
// This is to simulate the slow main memory.
// Multilevel cache can be used the cache contents of the file source.
// Implements the MemoryInterface functions fetch and store on the datasource.txt file.
// Template arguments:
//                      Key - Type of Key to identify the data in the file.
//                      Value - Type of the data.
//                      Converter - Converts the value to/from the type supported by the filesystem. 
//////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value, typename Converter, typename = MemoryInterface<Key, Value>, int = 0>
struct FileDataSource : MemoryInterface<Key, Value>
{
	// Fetches the data from the file identified by key.
	std::optional<Value> fetch(const Key& key)
	{
		std::ifstream ifs(fs::current_path().generic_string() + "/datasource.txt");
		if (!ifs.is_open())
		{			
			std::cerr << "ERROR:::source file datasource.txt not found" << std::endl;
			std::cerr << "ERROR:::Search path is " << fs::current_path().generic_string() << std::endl;
			return std::nullopt;
		}

		std::string line;
		while (std::getline(ifs, line))
		{
			Value v = Converter::string_to_data(line);

			if (v.key == key)
			{
				return v;
			}
		}
		return std::nullopt;
	}

	// Stores the data to the file.
	bool store(const Key& key, const Value& value, bool setdirty = true)
	{
		try
		{
			std::ifstream ifs(fs::current_path().generic_string() + "/datasource.txt");

			if (!ifs.is_open())
			{
				std::cerr << "ERROR:::source file datasource.txt not found" << std::endl;
				std::cerr << "ERROR:::Search path is " << fs::current_path().generic_string() << std::endl;
				return false;
			}

			std::ofstream temp("temp.txt");

			if (!temp.is_open())
			{
				std::cerr << "temp file temp.txt cannot be opened" << std::endl;
				ifs.close();
				return false;
			}
			bool found = false;

			std::string line;
			while (std::getline(ifs, line))
			{
				Value v = Converter::string_to_data(line);

				if (v.key == key)
				{
					temp << Converter::to_string(value) << std::endl;
					found = true;
				}
				else
				{
					temp << line << std::endl;
				}
			}
			if (!found)
			{
				temp << Converter::to_string(value) << std::endl;
			}


			ifs.close();
			temp.close();

			std::string srcfile = (fs::current_path().generic_string() + "/datasource.txt");
			auto retvalue = std::remove(srcfile.c_str());
			if (retvalue == 0)
			{
				retvalue = std::rename("temp.txt", srcfile.c_str());
			}

			if (retvalue != 0)
			{
				std::cout << "rewriting " << srcfile << " failed " << std::endl;
			}

			return (retvalue == 0);
		}

		catch (...)
		{
			return false;
		}

	}
};

// Type of the data stored in the file.
// Implements helper functions to facilitate conversion to and from std::string.
struct Data
{
	unsigned long key;
	std::string dog_name;
	std::string gender;
	std::string year_of_birth;
	std::string breed;
	std::string license_issued_year;

	static std::string to_string(const Data& e)
	{
		return std::to_string(e.key) + "," + e.dog_name + "," + e.gender + "," + e.year_of_birth + "," + e.breed + "," + e.license_issued_year;
	}

	static Data string_to_data(const std::string& line)
	{
		std::stringstream ss(line);
		char delimiter = ',';
		std::string token;
		std::vector<std::string> v;
		while (std::getline(ss, token, delimiter))
		{
			v.push_back(token);
		}

		Data object;
		object.key = std::atol(v[0].c_str());
		object.dog_name = v[1];
		object.gender = v[2];
		object.year_of_birth = v[3];
		object.breed = v[4];
		object.license_issued_year = v[5];

		return object;
	}

	bool operator == (const Data& e) const
	{
		return e.key == key &&
			e.dog_name == dog_name &&
			e.breed == breed &&
			e.gender == gender &&
			e.year_of_birth == year_of_birth &&
			e.license_issued_year == license_issued_year;
	}

	bool operator != (const Data& e) const
	{
		return !(e == *this);
	}
};

// Partial template specialization of Cache of size 10.
template <typename K, typename V, typename HigherLevelMemory, int level>
using CacheOfSize10 = CacheMemory<K, V, HigherLevelMemory, level, 10>;

// Partial template specialization of Cache of size 20.
template <typename K, typename V, typename HigherLevelMemory, int level>
using CacheOfSize20 = CacheMemory<K, V, HigherLevelMemory, level, 20>;

// Partial template specialization of Cache of size 10000.
template <typename K, typename V, typename HigherLevelMemory, int level>
using CacheOfSize10000 = CacheMemory<K, V, HigherLevelMemory, level, 10000>;

// Partial template specialization of Cache of size 20000.
template <typename K, typename V, typename HigherLevelMemory, int level>
using CacheOfSize20000 = CacheMemory<K, V, HigherLevelMemory, level, 20000>;

// Partial template specialization of Cache of size 30000.
template <typename K, typename V, typename HigherLevelMemory, int level>
using CacheOfSize30000 = CacheMemory<K, V, HigherLevelMemory, level, 30000>;

// File Data source for which multi level caching has to be added.
template <typename K, typename V, typename HigherLevelMemory, int level>
using DataSource = FileDataSource<K, V, Data, HigherLevelMemory, level>;

int main()
{
	// MultiLevelCache instantiation.
	// Key is int and Value is Data.
	// Followed by ordered list of memory heirarchies with top level main source memory at the last.
	// MultiLevelCache will instantiate the ordered list of the memories recursively with the last 
	// main memory source in the top level base class instantiation.
	MultiLevelCache<int, Data, CacheOfSize10, CacheOfSize20, CacheOfSize10000, CacheOfSize20000, CacheOfSize30000, DataSource> multilevelcache;

	auto v = multilevelcache.fetch(1000);
	if (v.has_value())
	{
		std::cout << Data::to_string(v.value()) << std::endl;
	}

	v = multilevelcache.fetch(1000);
	if (v.has_value())
	{
		std::cout << Data::to_string(v.value()) << std::endl;
	}

	v = multilevelcache.fetch(10);
	if (v.has_value())
	{
		std::cout << Data::to_string(v.value()) << std::endl;
	}

	/*a = Data::string_to_data("10,2,3,4,5,23456");
	multilevelcache.store(10, a);*/

	v = multilevelcache.fetch(1000);
	if (v.has_value())
	{
		std::cout << Data::to_string(v.value()) << std::endl;
	}

	return 0;
}