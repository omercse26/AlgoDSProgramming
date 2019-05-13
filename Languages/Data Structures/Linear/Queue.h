/* 
 * File:   Queue.h
 * Author: omer.asif
 *
 * Created on January 25, 2013, 3:16 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H
#include "List.h"

template <typename T>
class Queue : protected List <T>
{
   protected:
   typedef List_Node<T> Node;    
   Node *back;
   
   public:
   Queue() : back(NULL) {}
   void Enqueue(T data)
      {
          insert(data);
          if (back == NULL)
              back = this->root;
      }
      
   T Dequeue()      
      {
          try {
            if (back == NULL)
                throw "No Elements";
            T temp = back->data;
            back = deleteNode(temp);
            if (this->root == NULL)
                back == NULL;
            return temp;
          }
          catch (const char* str)
          {
              cout << str << endl; exit(-1);
          }
      }
};


#endif	/* QUEUE_H */

