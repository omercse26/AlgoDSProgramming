/*
abcd
d 
	cd  bcd
		cbd
		cdb
	
	dc	bdc
		dbc
		dcb
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

char fullstring[] = "OMER";
int fullstringpos = 0;

char* insertati(char a, char* str, int i)
{
        int j;
	char* output = (char*) malloc (strlen(str) + 2);
              
	for (j=0; j<i; j++)
		output[j] = str[j];
	
	output [j] = a;
	
	for (j= i; j < strlen(str); j++)
		output[j+1] = str[j];
	        
        output[j+1] = '\0';     
		
	return output;
}	

void insert(char a, char* input)
{   
    
    for (int i=0; i < strlen(input)+1; i++)
	{
		char* str = insertati(a,input,i);
		
		if (strlen(str) == strlen(fullstring))
                {
			cout << str << endl;
                }
		else
		{
			fullstringpos++;
                        char chr = fullstring[fullstringpos];
			insert (chr, str);
                        fullstringpos--;
		}		
	}
}

int main()
{
	fullstringpos = 0;
        char str[] = "";     
        char a = fullstring[0];
	insert(a,str);
	return 0;
}		
				
		