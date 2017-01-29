#include <iostream>
using namespace std;
template <bool b>
class findcustom
{
    public:
        
	static void print() { cout << "not custom type\n"; }
};

template <>
class findcustom <true>
{
    public:
  static void print() { cout << "custom type\n"; }	
};

class custom_type
{
	int a;
	int b;
};

template<typename T>
class custom_type_traits
{
public:
	static const bool iscustom=false;
};

template<>
class custom_type_traits<custom_type>
{
public:
	static const bool iscustom=true;
};

template<typename T>
void print(T object)
{
   findcustom< custom_type_traits<T>::iscustom >::print();
}

int main()
{
    custom_type ct;
    print(10);
    print(ct);
    return 0;
}
