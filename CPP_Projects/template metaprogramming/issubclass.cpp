#include <iostream>
using namespace std;

template <class T, class U>
class Conversion
{
   typedef char Small;
   class Big { char dummy[2]; };
   static Small Test(U); // This is the key
   static Big Test(...); // This will be selected if not convertible
   static T MakeT();
public:
   enum { exists =
      sizeof(Test(MakeT())) == sizeof(Small) };
};

struct A
{
    int a;   
};

struct B:public A
{
    int b;
};

struct C
{
    int c;
};

int main()
{
   using namespace std;
   cout << "Is B a subclass of A " << Conversion<B*,A*>::exists;
}

