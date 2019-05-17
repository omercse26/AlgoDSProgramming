#include <iostream>
using namespace std;

//#define DEBUG(str) cout << __FILE__ << ": " << str << " "<< endl

#define DEBUG(str) 

struct FreeList
{
    void *head;
    FreeList* next;
};
class Rational1 {
public:
    Rational1 (int a = 0, int b = 1 ) : n(a), d(b) {}
private:
    int n;   // Numerator
    int d;   // Denominator
};

class Rational
{
public:
	Rational (int a = 0, int b = 1 ) : n(a), d(b) {}
	static void* operator new(size_t);
	static void operator delete(void*, size_t);
        static void expand_the_list();
private:
    int n;
    int d;
    static FreeList* freelist;
};

FreeList* Rational::freelist = NULL;

void* Rational::operator new (size_t)
{	
	Rational* curr;
	if (freelist)
	{
		DEBUG("freelist is not null");
		curr = static_cast<Rational*>(freelist->head);
	}
	else
	{
		DEBUG("freelist is nullexpand the freelist");
                expand_the_list();
		curr = static_cast<Rational*>(freelist->head);
                freelist = freelist->next;
	}
	return curr;
}	

void Rational::operator delete(void* p, size_t)
{
    DEBUG ("");
    FreeList *curr = new FreeList();
    curr->head = p;
    curr->next = freelist;
    freelist = curr;        
}

void Rational::expand_the_list()
{
    DEBUG ("");
    if (freelist == NULL)
    {
        freelist = reinterpret_cast<FreeList*> (new char[sizeof(FreeList)]);
        freelist->head = static_cast<void *> (new char[sizeof(Rational)]);
        freelist->next = NULL;
    }
    for (int i=1; i<64; i++)
    {
        FreeList *temp =  reinterpret_cast<FreeList*> (new char[sizeof(FreeList)]);
        temp->head = static_cast<void *> (new char[sizeof(Rational)]);
        temp->next = freelist;
        freelist = temp;
    }
}

int main()
{
    Rational *array[1000];
    
    // Start timing here

    for (int j = 0; j < 5000; j++)   {
         for (int i = 0; i < 1000; i++)   {
              array[i] = new Rational(i);
              }
         for (int i = 0; i < 1000; i++)   {
              delete array[i];
              }
         }

}         