/* 
 * File:   List_Node.h
 * Author: omer.asif
 *
 * Created on January 24, 2013, 7:32 PM
 */

#ifndef LIST_NODE_H
#define	LIST_NODE_H
#include <iostream>

template <typename T>
struct List_Node 
{
   T data;
   List_Node<T> *next;
   
   public:
   List_Node(T a): data(a), next(NULL) {}
   List_Node(T a, List_Node<T>* ptr): data(a), next(ptr){} 
   void deleteAllNodes()
   {
       List_Node<T>* temp = this, *prev;
       
       
       while (temp)
       {
           prev = temp->next;
           delete temp;
           temp = prev;
       }
   }
};

#endif	/* LIST_NODE_H */

