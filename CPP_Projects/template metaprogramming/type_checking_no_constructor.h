#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
using namespace std;


template<class T> struct SimpleType {   
    enum {value = 0};
};
template<class T> struct SimpleType<T *> {
  enum {value = 1};
};
template<class T> struct SimpleType<const T> {
  enum {value = SimpleType<T>::value};
};
template<class T, size_t n> struct SimpleType<T[n]> {
  enum {value = SimpleType<T>::value};
};
//#define isTypeSimple(T) ((bool) SimpleType<T>::value) 
#define SIMPLETYPE(T)				\
template<> struct SimpleType<T> {		\
  union {					\
    T t;					\
  } catcherr;					\
  enum {value = 1};				\
}

struct A
{
    int a;       
};

SIMPLETYPE(int);
SIMPLETYPE(A);

template <typename T>
bool istypesimp(SimpleType<T> a)
{
    return (bool)SimpleType<T>::value;
}
 
template <typename T>
bool istypesimp(T a)
{
    return (bool)SimpleType<T>::value;
}

int main()
{   
    SimpleType<int> _a;
    A b;
    int status;
    cout << abi::__cxa_demangle(typeid(_a).name(), NULL, NULL, &status) << endl;    
    cout << "simple type: " << istypesimp(b) << endl;   
    return 0;
    
}