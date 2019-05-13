#include <iostream>
using namespace std;

class A
{
public:
	const int a;
	mutable int b;

	A(): a(0) {}
	void print() const
	{
		b = 10;
		cout << a << b << endl;
	}
};


int main()
{
	A x;
	A b = x;
	
	b.print();

	const A y;
	y.print();

	return 0;
}
