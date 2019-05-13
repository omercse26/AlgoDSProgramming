// CPP_Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Basic.h"

using namespace std;

int main()
{
	using S = IntVector<5,4,3,2,1,0>;
	cout << At<S, 3>::value << endl;
	cout << At <PushFront<S, 10>::Type, 0>::value << endl;

	cout << At <PushBack<S, 10>::Type, 6>::value << endl;

	cin.ignore();
    return 0;
}
