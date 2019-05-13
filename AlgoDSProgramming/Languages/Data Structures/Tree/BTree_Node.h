/* 
 * File:   BTree_Node.h
 * Author: omer.asif
 *
 * Created on January 24, 2013, 7:33 PM
 */

#ifndef BTREE_NODE_H
#define	BTREE_NODE_H
#include <iostream>
using namespace std;
template <typename T>
struct BTree_Node 
{
   typedef BTree_Node<T> Node;
   T data;
   BTree_Node<T> *left;
   BTree_Node<T> *right;
   
   public:
   BTree_Node(T a): data(a), left(NULL), right(NULL) {}  
   void deleteAllNode()
   {
       //cout << "deleteAllNopde" << endl;
       Node* temp = this;
       if (temp != NULL)
       {
           (this->left)->deleteAllNode();
           (this->right)->deleteAllNode();
       }
       delete temp;
   }
};

#endif	/* BTREE_NODE_H */

