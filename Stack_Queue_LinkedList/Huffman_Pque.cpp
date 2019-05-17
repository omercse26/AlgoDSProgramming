#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#inlcude "PQueue.h"
using namespace std;

struct Tree
{
    char value;   
    int key;
    struct Tree* left;
    struct Tree* right;
    
    Tree(char val,int key): value(val),key(key) {}
};

Tree* huffman(PQueue<Tree*>& queue)
{
    while (queue.count > 1)
    {
        Tree* node1 = queue.deque();
        Tree* node2 = queue.deque();
        
        Tree* parent = new Tree('#',node1->key+node2->key);
        parent->left = node1;
        parent->right = node2;
        
        queue.enqueue(parent,parent->key);        
    }    
    return queue.deque();    
}

void huffman_encoding(Tree* tree, string prefix, map<char,string>& huffmap )
{
    
    if (tree->value!='#')
    {
        huffmap[tree->value] = prefix;
    }
    else
    {
        string leftprefix = prefix;
        leftprefix += "1";
        huffman_encoding (tree->left,leftprefix,huffmap);
        
        string rightprefix = prefix;
        rightprefix += "0";
        huffman_encoding(tree->right,rightprefix,huffmap);        
    }
    
    
}


/* We need both the huffman tree and the encoded file to decode */

void huffman_decoding (Tree* tree)
{
    ifstream infile;
    infile.open("out");
    ofstream outfile;
    outfile.open("decoded");
    char c;
    Tree* temp = tree;
    while (infile.get(c))
    {        
        if ( c == '1' && temp->left->value == '#')
            temp = temp->left;
        else if (c == '0' && temp->right->value == '#')
            temp = temp->right;
        else
        {
            if ( c=='1')
                outfile << temp->left->value;
            else 
                outfile << temp->right->value;
            temp = tree;
        }
            
    }
    
    infile.close(); outfile.close();
    
    
}

int main()
{
    	ifstream infile;
        char c;
        map<char,int> character;
	infile.open ("newfile");
        
        while(infile.get(c)) 
        {
                if (character.find(c) == character.end())
                    character[c] = 1;
                else
                    character[c] = ++character[c] ;        
        }
        infile.close();
        
        
        map<char,int>::iterator it = character.begin();
        PQueue<Tree*> pqueue;
        
        for (;it != character.end();it++)
        {
            Tree* tree = new Tree (it->first,it->second);            
            pqueue.enqueue(tree,it->second);
        }
        
        Tree* htree = huffman(pqueue);
        
        string prefix = "";
        map<char,string> huffmap;
        huffman_encoding(htree, prefix, huffmap);  
        
        ifstream file;
        file.open("newfile");
        ofstream outfile;
        outfile.open("out");
        
        while(file.get(c)) 
        {
            outfile << huffmap[c]; 
        }
        map<char,string>::iterator it3;
        /*for ( it3= huffmap.begin(); it3 != huffmap.end(); it++)
            cout << it3->first << "  " << it3->second << endl;*/
        
        file.close();
        outfile.close();
        
        
        huffman_decoding(htree);        	
}
	
