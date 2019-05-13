#pragma once
#include <iostream>
using namespace std;

struct A
{
	bool serialize()
	{
		cout << "I am A";
		return true;
	}
};

template <typename LambdaType>
struct Test
{
	template <typename Type>
	constexpr auto hasSerialize(Type&& type)
		-> decltype(declval<LambdaType>() (declval<Type>()), std::true_type())
	{
		// below line works.
		//decltype(declval<Type>().serialize()) && t = bool();

		// declval of Lambda type never works in function body
		//decltype(declval <LambdaType>()) a = declval <LambdaType>();

		//return true;
	}

	constexpr auto hasSerialize(...)
		-> decltype (std::false_type())
	{
		return std::false_type();
	}
	//LambdaType&& ltype;
};

int mainfunc()
{
	auto lambda = [&](auto&& a) -> decltype(a.serialize()) {};
	Test<decltype(lambda)> test;
	cout << decltype(test.hasSerialize(A()))::value;

	lambda(A());
	return 0;
}
