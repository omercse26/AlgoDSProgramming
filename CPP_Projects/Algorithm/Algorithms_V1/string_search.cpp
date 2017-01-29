#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <set>

using namespace std;
using namespace boost;
std::set<string> bucket;
string text2 = "this a test programming";

int insert(string& str, int i,int end)
{
    char_separator<char> sep(". ");
    tokenizer< char_separator<char> > tokens(str, sep);
    int j = 0;
        
    bucket.clear();
    BOOST_FOREACH (const string& t, tokens) 
    {       
        if (j >= i && j <= end)
            bucket.insert(t);
        j++;
    }
    
  
    
    int found = 1;
    tokenizer< char_separator<char> > src(text2, sep);
    BOOST_FOREACH (const string& t, src) 
    {
        if (bucket.find(t) == bucket.end())
        {            
            found = 0;
            break;
        }
    }
                
    return found;
    
    
}


int main(int, char**)
{
    string text = "This is a test. This is a programming test. This is a programming test in any language.";
    std::transform(text.begin(), text.end(),text.begin(), ::tolower);      
    
    char_separator<char> sep(". ");
    tokenizer< char_separator<char> > tokens(text, sep);
    int textlen = 0;
    
    BOOST_FOREACH (const string& t, tokens) 
    {
      textlen++;    
    }
 
    
    int text2len = 0;
    tokenizer< char_separator<char> > src(text2, sep);

    BOOST_FOREACH (const string& t, src) 
    {
      text2len++;    
    }
    
    for (int start = text2len; start <= textlen; start++)
        for (int i = 0; (i+start-1) < textlen; i++)
        {
           int found = insert(text,i,i+start-1);
           if (found)
           {
               cout << "string found between ";
               cout << i << " and " << (i+start-1);
               return 0;
           }
        }
    
    
    cout << "String Not Found" << endl;
    return 0;
            
    
}