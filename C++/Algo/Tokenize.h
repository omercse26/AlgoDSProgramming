#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Input a  String and set of delimiters.
// include_delim : flag to include the delimiter also in the tokens.
vector<string> tokenize(const string& str, const string& delim, bool include_delim)
{
    size_t pos = 0,not_delim,nextspace;
    vector<string> vec;
    char a;

    while (pos != string::npos)
    {
           not_delim = str.find_first_not_of(delim,pos);

           if (not_delim == string::npos)
              not_delim = str.length() - 1;

           nextspace = str.find_first_of(delim,not_delim+1);
           
           if (nextspace != string::npos)
             {
                //cout << "Tokenize: " << str[nextspace] <<endl;
                if (include_delim)
                   vec.push_back(string(1,str[nextspace]));
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

int main()
{
    string str = "who is taking a challenge? in life.wgath";
    
    vector<string> vec = tokenize(str,"?. ", true);
    
    for (vector<string>::iterator it = vec.begin(); it!=vec.end(); it++)
        cout << *it << ":";
    
    cout << endl;
    
    
}