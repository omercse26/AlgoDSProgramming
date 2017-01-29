#include <iostream>
#include <algorithm>
using namespace std;
bool equal(int,int);
template <class Func, class Val>
class Binder
{
	Func f;
	Val constant;
  public:             
	Binder(Func func,Val value) : f(func), constant(value){}

	bool operator()(Val arg)
	{
		return f(arg,constant);
        }		
};

template <class Func, class Val>
Binder<Func, Val> bind(Func f,Val t)
{
   return Binder<Func, Val>(f,t);
}

bool eq(int i,int j)
{
    return (i==j);
}

int main ()
{
   int numbers[] = {10,20,30,40,50,10};
  int cx;
  cx = count_if (numbers, numbers+6, bind(eq,10) );
  cout << "There are " << cx << " elements that are equal to 10.\n";
  return 0;
}
