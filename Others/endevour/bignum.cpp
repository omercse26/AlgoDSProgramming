#include<iostream.h>
using namespace std;
#define MAXDIGITS 100

#define PLUS 1
#define MINUS -1



class bignum
{
  private:
                char digits[MAXDIGITS];
                int signbit;
                int lastdigit;

    public:

    void make_num(char *s)
    {
               if (*s == '-')
                 signbit = MINUS;
               else
                 signbit = PLUS;
               strcpy(s,digits);
               lastdigit=strlen(digits)-1;
    }

    void print_num()
    {
		char *s = digits;
		if (signbit == MINUS) cout << '-';
		while (*s)
		{
           cout << *s++;
	    }
	}

};

int main()
{
	bignum sample;
	sample.make_num("100");;
	sample

