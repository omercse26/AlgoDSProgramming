#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Tr
{
    Tr *index[26];
    bool fullword;
public:
    
    Tr(): fullword(false)
    {
        for (int i=0; i<26;i++)
            index[i] = NULL;
    }
    
    void add(const char* s)
    {
        int i = (*s++) - 'a';
        Tr* curr = this;
        
        while (curr->index[i] != NULL)
        {
            curr = curr->index[i];
            i = (*s++) - 'a';
        }
        
        Tr *temp = new Tr();
        temp->fullword = true;
        curr->index[i] = temp;        
        
    }
    
    void printAll(vector<string>& word,string& s, Tr* curr=NULL)
    {
        curr = (curr==NULL?this:curr);
                
        for (int i=0; i<26; i++)
        {
            if (curr->index[i] != NULL)
            {
                s = s + char(i+'a');
                if (curr->index[i]->fullword)
                    word.push_back(s);
                printAll(word,s, curr->index[i]);
            }
                    
        }
        
    }
    
    void printAllWords(vector<string>& word,string& s,const char* str, Tr* curr=NULL)
    {
        curr = (curr==NULL?this:curr);
        int i = (*str)-'a';
        
        while(*str != '\0')
        {
            s = s + (*str);            
            curr = curr->index[i];
            
            if (curr->fullword)
                word.push_back(s);
            
            str++;
        }
        
        printAll(word,s,curr);
    }
};

int main()
{
    Tr tr;
    tr.add("a");
    tr.add("add");
    tr.add("addit");
    
    string s;
    vector<string> vec;
    
    tr.printAllWords(vec, s, "a");
    
    for (vector<string>::iterator it = vec.begin(); it!=vec.end(); it++)
    {
        cout << "element " << *it << endl;
    }
    return 0;
}