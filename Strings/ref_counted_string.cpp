#include <memory>
#include <iostream>
#include <mutex>

class RefCountedString
{
	struct Holder
	{
		std::string _str;
		int _refcount;
		std::mutex _m;

		Holder(std::string s) : _str(std::move(s)), _refcount(1)
		{

		}

		int getRefCount()
		{
			std::lock_guard<std::mutex> lock(_m);
			return _refcount;
		}

		void incRefCount()
		{
			std::lock_guard<std::mutex> lock(_m);
			++ _refcount;
		}

		void decRefCount()
		{
			std::lock_guard<std::mutex> lock(_m);
			++_refcount;
		}
	};

	Holder* stringholder_;

	RefCountedString(std::string s): stringholder_ (new Holder(std::move(s)))
	{

	}

	RefCountedString(const RefCountedString& other)
	{
		this->stringholder_ = other.stringholder_;
		this->stringholder_->incRefCount();
	}

	void detachRefCountedString()
	{
		this->stringholder_->decRefCount();
		if (this->stringholder_->_refcount == 0)
		{
			delete this->stringholder_;
			this->stringholder_ = nullptr;
		}
	}

	RefCountedString& operator = (const RefCountedString& other)
	{
		if (this == &other) return *this;
		detachRefCountedString();
		this->stringholder_ = other.stringholder_;
		this->stringholder_->incRefCount();
	}

	~RefCountedString()
	{
		detachRefCountedString();
	}
};