
//	Compile Time Introspection
//	https://jguegant.github.io/blogs/tech/sfinae-introduction.html


#pragma once
#include <iostream>
using namespace std;

/////////////////////// Data //////////////////////////////////////////////////
struct A
{};

void to_string(A& a)
{
	std::cout << "I am A" << std::endl;
}

struct B
{
	int serialize;
};

void to_string(B& a)
{
	std::cout << "I am B" << std::endl;
}

struct C
{
	void serialize()
	{
		std::cout << "Serialize: I am C" << std::endl;
	}
};

///////////////////////// End Of Data /////////////////////////////////////////////

/////////////////////////// enable if ///////////////////////////////////////////////////

template <bool b, typename T>
struct enable_if {};

template <true, typename T>
struct enable_if
{
	typedef T type;
};

template <typename T>
void test(enable_if<false, T> e)
{
	std::cout << "does not have serialize" << std::endl;
}

template <typename T>
void test(enable_if<true, T>::type e)
{
	std::cout << "has serialize" << std::endl;
}

////////////////////////// end of enable if /////////////////////////////////////////////

//////////////////////////// OLD STYLE //////////////////////////////////////////////////////




//////////////////////////// END OF OLD STYLE ///////////////////////////////////////////////

void testsfinae_reflection()
{
	A a;
	B b;
	C c;


	//serialize(a);
	//serialize(b);
	//serialize(c);
}