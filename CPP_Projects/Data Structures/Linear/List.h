/* 
 * File:   List.h
 * Author: omer.asif
 *
 * Created on January 24, 2013, 8:07 PM
 */

#ifndef LIST_H
#define	LIST_H
#include <iostream>
#include "List_Node.h"

using namespace std;
template <typename T>

class Iterator;

class List
{
protected:
  typedef List_Node<T> Node;
  Node *root;
  
public:  
  List(): root (NULL) {};
  ~List(){root->deleteAllNodes();}
  
  void insert(T);
  Node* deleteNode(T);
  void print();
  Node* first() { return root; } 
  Iterator begin() { return new Iterator(this); }
};

template <typename T>
void List<T>::insert(T data)
{
   if (root == NULL)   
      root = new Node(data);
   else
   {
     Node* temp = new Node(data,root);
	 root = temp;
   }
}

template <typename T>
List_Node<T>* List<T>::deleteNode(T data)
{
   if (root == NULL)   
      return NULL;
   
   Node *temp = root;
   Node *prev = NULL;
   while (temp)
   {
      if (temp->data == data)
	  {
		 if (temp == root)
			root = temp->next;
		 else
			prev->next = temp->next;
	         delete temp;
		 return prev;
	  }	  
	  prev = temp;
	  temp = temp->next;	     
   }
   return NULL;
}

template <typename T>
void List<T>::print()
{

  for (Node *temp = root; temp != NULL; temp = temp->next)
     cout << temp->data << " ";
  cout << endl;
}

#endif	/* LIST_H */

