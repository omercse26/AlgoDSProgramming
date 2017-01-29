/* 
 * File:   Stack.h
 * Author: omer.asif
 *
 * Created on January 25, 2013, 2:52 PM
 */

#ifndef STACK_H
#define	STACK_H

#include "List.h"


template <typename T>
class Stack: protected List<T>
{
    public:
        
    void Push(T data)
    {
        insert (data);
    }
    
    T Pop ()
    {
      try {
        if (this->root == NULL)
            throw "No Elements";
          
        T temp = this->root->data;        
        deleteNode(temp);
        return temp;
      }
      
      catch (char const * s)
      {
              cout << s << endl; exit(-1); 
      }
    }
    
};

#endif	/* STACK_H */

