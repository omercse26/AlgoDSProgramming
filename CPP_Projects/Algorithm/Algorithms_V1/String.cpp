#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
using namespace std;


void reverseString( string str)
{
    //cout << "string " << str << endl;
    int start = str.find_first_not_of(" ",0);        
    int end = str.find_first_of(" ",0);    
    if (end == string::npos)
    {
        cout << str << endl; return;
    }
    else
        reverseString (str.substr(end+1));
    cout << str.substr(start, end) << endl;
    
}

int strcmp (const char* a, const char* b) 
{
    try {
        if (a == NULL || b == NULL) throw (3);
        //register int dist = 'A' - 'a';
        //while ((*a && *b) && ((*a == *b || (*a+dist) == *b || *a == (*b+dist))))
        while ((*a && *b) && (*a == *b || (*a^32) == *b))
        
        {
            a++; b++;
        }
        return *a-*b;
    }
    catch (int a)
    {        
         throw;
    }
    
}

void strcpy (const char* a, char* b)
{
    while (*b++ = *a++) {}
    
}

void strcpy (const char* a, char* b, int  n)
{
    while (n-- && (*b++ = *a++)) {}
    
}

/* Function to calculate x raised to the power y in O(logn)*/
int power(int x, unsigned int y)
{
    int temp;
    cout << "calculating x " << x << " y " << y <<endl;
    if( y == 0)
        return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
        return x*temp*temp;
}

int main()
{
    reverseString("omer asif is intelligent");
}