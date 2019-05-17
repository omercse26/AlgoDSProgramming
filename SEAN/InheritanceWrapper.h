#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

//using object_t = int;

template <typename T>
void draw(const T& t, ostream& out, size_t position)
{
	out << std::string(position, ' ') << t << std::endl;
}

class object_t
{
public:
	template <typename T>
	object_t(T i) : self_(make_unique<model_t<T>>( move(i) )) 
	{
		//cout << "ctor" << endl;
	}

	/*object_t(string s) : self_( make_unique<string_model_t>(s) ) {}*/

	object_t(const object_t& obj) : self_(obj.self_->_copy())
	{
		//cout << "copy" << endl;
	}

	object_t& operator = (const object_t& obj)
	{
		cout << "assign" << endl;
		object_t tmp(obj);
		//self_ = move(tmp.self_);
		*this = move(tmp);
		return *this;
	}

	object_t(object_t&&) noexcept = default;

	object_t& operator = (object_t&& obj) noexcept = default;
	/*{
		cout << "move assign" << endl;
		self_ = move(obj.self_);
		return *this;
	}*/

	friend void draw(const object_t& obj, ostream& out, size_t position)
	{
		obj.self_->draw_(out, position);
	}

private:
	struct concept_t 
	{
		virtual ~concept_t() = default;
		virtual concept_t* _copy() = 0;
		virtual void draw_(ostream& out, size_t position) const = 0;
	};

	template <typename T>
	struct model_t : concept_t
	{
		model_t(T i) : x(move(i)) {}
		concept_t* _copy() { return new model_t<T>(*this); }
		void draw_(ostream& out, size_t pos) const
		{
			draw(x, out, pos);
		}
	private:
		T x;
	};

	/*struct int_model_t : concept_t
	{
		int_model_t(int i) : x( move(i) ) {}

		concept_t* _copy() { return new int_model_t(*this);  }
		void draw_(ostream& out, size_t position) const
		{
			draw(x, out, position);
		}

	private:
		int x;
	};

	struct string_model_t : concept_t
	{
		string_model_t(string s) : x(move(s)) {}

		concept_t* _copy() { return new string_model_t(*this); }

		void draw_(ostream& out, size_t position) const
		{
			draw(x, out, position);
		}

	private:
		string x;
	};*/

	unique_ptr <concept_t> self_;
};

using document_t = std::vector<object_t>;

//void draw(const string& s, ostream& out, size_t position)
//{
//	out << string(position, ' ') << s << endl;
//}

void draw(const document_t& x, ostream& out, size_t position)
{
	out << std::string(position, ' ') << "<document>" << std::endl;

	for (const auto& e : x)
	{
		draw(e, out, position);
	}

	out << std::string(position, ' ') << "</document>" << std::endl;
}

object_t func()
{
	cout << "func()::begin" << endl;
	object_t o = 5;
	cout << "func()::initialized" << endl;
	return o;
}

void main_draw()
{
	document_t doc;
	doc.reserve(5);

	doc.emplace_back(1);
	doc.emplace_back(2);
	doc.emplace_back(3);

	doc.emplace_back("string");

	draw(doc, std::cout, 1);

	reverse(doc.begin(), doc.end());

	/*object_t t = 0;
	cout << "main_draw::initialized" << endl;

	t = func();*/
}

