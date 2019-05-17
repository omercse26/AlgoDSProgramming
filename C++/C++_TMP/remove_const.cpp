#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
using namespace std;

template <class T>
struct remove_const
{
	typedef T type;
};

template <class T>
struct remove_const <T const>
{
	typedef T type;
};

int main()
{
    int i;
	typedef remove_const<int>::type type1;
	typedef remove_const<int const>::type type2;                
	
	type1 a;
	type2 b = 10;
        b=1;
	
        cout << abi::__cxa_demangle(typeid(a).name(),0,0,&i) << endl;
	cout << abi::__cxa_demangle(typeid(b).name(),0,0,&i) << endl;              
        
	return 0;

}