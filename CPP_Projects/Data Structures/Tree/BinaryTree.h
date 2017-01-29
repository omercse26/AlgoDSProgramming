/* 
 * File:   BinaryTree.h
 * Author: omer.asif
 *
 * Created on January 24, 2013, 8:14 PM
 */

#ifndef BINARYTREE_H
#define	BINARYTREE_H

#include <iostream>
#include "BTree_Node.h"

using namespace std;

template <typename T>
class BinaryTree
{
private:
    
   typedef BTree_Node<T> Node;
   Node* root;
   
   void printInOrder(Node*);
   int sizeofTree(Node*);
   int countLeaves(Node *);
   int isEqual(Node* , Node*);
   Node* createMirror(Node* root);
   void printAllPath(Node *,int[], int);
   int hasPathSum (Node*, int);
    
public:   
   BinaryTree():root(NULL) {} 
   ~BinaryTree() {root->deleteAllNode();}
   
   Node* ConstructFromPrePost(int*, int* , int* , int , int , int);
   Node* ConstructFromInPre(T*, T* , int* , int , int);
   
   void print();   
   int sizeofTree();
   int countLeaves();   
   int isEqual(BinaryTree<T>& bt);   
   void createMirror(BinaryTree<T>&);   
   void printAllPath();
   int hasPathSum (int);
  
};

template <class T>
void BinaryTree<T>::print()
{
  printInOrder(root);
}

template <class T>
void BinaryTree<T>::printInOrder(Node* temp)
{
   if (temp == NULL)
      return;
   printInOrder (temp->left);
   cout << temp->data << " ";
   printInOrder  (temp->right);
}   

template <typename T>
typename BinaryTree<T>::Node* 
BinaryTree<T>::ConstructFromPrePost (int* pre, int*post, int* preIndex, int low, int high, int size)
{ 
   typedef BinaryTree<T>::Node Node;   
   
   Node* temp = new Node(pre[*preIndex]);  
   
   if (root == NULL) 
      root = temp;
   
   ++*preIndex;
   
   if (low == high)  
       return temp;  
   
   int i;
   for (i = low; i <= high; i++)
      if (post[i] == pre[*preIndex])
       break;                  
   
   temp->left  = ConstructFromPrePost(pre, post, preIndex, low, i, size);
   temp->right = ConstructFromPrePost(pre, post, preIndex, i+1, high-1, size);
   return temp;
}

template <typename T>
typename BinaryTree<T>::Node* 
BinaryTree<T>::ConstructFromInPre (T *pre, T *in, int *preIndex, int low, int high)
{
    Node *temp = new Node(pre[*preIndex]);
     //cout << "ConstructFromInPre " << low << " " << high << " " << *preIndex << endl;
    if (root == NULL)
        root = temp;    
    
    int i;
    for (i = low; i <= high; i++)
        if (in[i] == pre[*preIndex])
            break;
    
    ++*preIndex;
    if (low == high)
        return temp;
    if (i != low)
       temp->left  = ConstructFromInPre(pre,in, preIndex,low,i-1);
    if (i != high)
        temp->right = ConstructFromInPre(pre, in, preIndex, i+1, high);
    return temp;
}

template <typename T>
int BinaryTree<T>::sizeofTree(Node *temp)
{
    if (temp == NULL) 
        return 0;
    
    return sizeofTree(temp->left)+sizeofTree(temp->right)+1;        
    
}

template <typename T>
int BinaryTree<T>::sizeofTree()
{
    return sizeofTree(root);
}

template <typename T>
int BinaryTree<T>::countLeaves(Node *temp)
{        
    
    if (temp->left == NULL && temp->right == NULL)
        return 1;
    
    return countLeaves (temp->left) + countLeaves(temp->right);        
    
}


template <typename T>
int BinaryTree<T>::countLeaves()
{
    return countLeaves(root);
}

template <typename T>
int BinaryTree<T>::isEqual(BinaryTree<T>& bt)
{
    //cout << "starrted \n" << endl;
    int equ =  isEqual (this->root, bt.root);    
    //cout << "ended \n" << endl;
    return equ;
}

template <typename T>
int BinaryTree<T>::isEqual(Node* root1, Node* root2)
{
    
    if (root1 == NULL && root2 == NULL)   
        return 1;    
    else if ((root1 == NULL || root2 == NULL))        
        return 0;               
    else
    {      
      int left =  isEqual (root1->left, root2->left);
      int right = isEqual(root1->right, root2->right);     
      return  left && right; 
    }
}

template <typename T>
typename BinaryTree<T>::Node*
BinaryTree<T>::createMirror(Node* root)
{
    if (root == NULL)
        return NULL;
    Node* temp  = new Node(root->data);
    temp->left  = createMirror(root->right);
    temp->right = createMirror (root->left);
    return temp;
}

template <typename T>
void BinaryTree<T>::createMirror(BinaryTree<T>& bt)
{
    bt.root = createMirror(root);
}

template <typename T>
void BinaryTree<T>::printAllPath()
{
    int array[100];
    printAllPath(root, array, 0);
}

template <typename T>
void BinaryTree<T>::printAllPath(typename BinaryTree<T>::Node* node, int array[], int index)
{       
    array[index++] = node->data;    
    
     if (node->left == NULL && node->right == NULL)
    {
        for (int i = 0; i <index; i++)
            cout << array[i] << " ";
        cout << endl;
        return;
    }
    
    printAllPath(node->left, array, index);
    printAllPath(node->right, array, index);
}

template <typename T>
int BinaryTree<T>::hasPathSum(int sum)
{
    return hasPathSum(root,sum);
}

template <typename T>
int BinaryTree<T>::hasPathSum(Node* node, int sum)
{    
    if (node->left == NULL && node->right == NULL)
    {
        sum -= node->data;
        return (sum == 0);        
    }
    
    sum -= node->data;
    return hasPathSum (node->left, sum) || hasPathSum(node->right,sum);
}

#endif	/* BINARYTREE_H */

