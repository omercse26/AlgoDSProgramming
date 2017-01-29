/* 
 * File:   main.cpp
 * Author: omer.asif
 *
 * Created on November 22, 2012, 6:47 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

std::set<string> bucket;

vector<string> tokenize(const string& str, const string& delim)
{
    size_t pos = 0,not_delim,nextspace;
    vector<string> vec;
	
    while (pos != string::npos)
    {        
           not_delim = str.find_first_not_of(delim,pos);
           
	   if (not_delim == string::npos)	   
		not_delim = str.length() - 1;			
			
	   nextspace = str.find_first_of(delim,not_delim+1);
	   if (nextspace != string::npos) 
	   {						
			vec.push_back (str.substr(not_delim,nextspace - not_delim));
			pos = nextspace+1; 
	   }
	   else
	   {              
			if ((str.length() - 1 - not_delim) > 0)  
			    vec.push_back (str.substr(not_delim));                        
			pos = string::npos;	        	  
	   }
    }	
    return vec;
}

int find(const vector<string>& str, int i,int end)
{
    int j = 0; int found = 1;
       
    for (j = i; j <= end; j++)    
        if (bucket.find(str[j]) == bucket.end())
        {            
            found = 0;
            break;
        }  
                
    return found;        
}

int main(int argc, char** argv) {

    string text = "This is a test. This is a programming test. This is a programming test in any language.";
    string text2 = "this a test programming ";
    std::transform(text.begin(), text.end(), text.begin(), (int (*)(int)) std::tolower);
    std::transform(text2.begin(), text2.end(), text2.begin(), (int (*)(int)) std::tolower);
    
    vector<string> vec1(tokenize(text,". "));
    vector<string> vec2(tokenize(text2,". "));       
    
    int textlen = vec1.size();
    int text2len = vec2.size();
    bucket.clear();
    for (int j=0; j<text2len; j++)               
        bucket.insert(vec2[j]);
    
    int found = 0, first, last;
    
    for (int start = text2len; start <= textlen && found == 0; start++)
        for (int i = 0; (i+start-1) < textlen; i++)
        {
           found = find(vec1, i,i+start-1);
           if (found)
           { 
               first = i;
               last = (i+start-1);
               break;
           }
        }
    
    if (found)
    {
       cout << endl;
       for (int i = first; i <= last; i++)
           cout << vec1[i] << " ";
       
       cout << endl;
    }
    else
    {
        cout << "String Not Found" << endl;    
    }
        
    return 0;
}

