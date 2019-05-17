#include <iostream>
using namespace std;

void swap (int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void print (int *a, int end)
{
    for (int i=0; i < end; ++i)
	{
	    cout << a[i] << " ";
	}
}

int main() {
	// your code goes here
	int a[] = {0,1,2,2,1,0};
	
	int x/*left are zeros*/, y /* 1s between x and y inclusive*/, z /*2s right of z*/, end;
	
	x = y = 0;
	end = sizeof(a)/sizeof(int);
	z = end - 1;
	
	while (z >=0 && a[z] == 2)
	{
	    --z;
	}
	
	while (y < end && y <= z)
	{
	    switch(a[y])
	    {
	        case 0:
	            if (x < y)
	            {
	                swap (a[x], a[y]);
	            }
	            ++x; ++y;
	            break;
	        case 1:
	            ++y;
	            break;
	        case 2:
	           swap (a[y], a[z]);
	           --z;
	           break; 
	    }
	}
	
	print (a, end);
	
	return 0;
}
