/* 
 * File:   BST.h
 * Author: omer.asif
 *
 * Created on February 15, 2013, 5:58 PM
 */

#ifndef BST_H
#define	BST_H
#include <iostream>
#include "BTree_Node.h"
template <typename T>
class BST
{
    typedef BTree_Node<T> Node;
    BTree_Node<T>* root;
    void print(Node* node);
    void insert(Node*, T);
    bool Delete(Node* &, T);
    public:
        BST(): root(NULL) {}
        ~BST() {  root->deleteAllNode(); }
        void printInOrder();
        void insert(T data);
        bool Delete(T data);
        
};

template <typename T>
void BST<T>::print(Node* node)
{
    if (node == NULL)
    {
       // cout << "BST::Test: Root null" << endl;
        return;
    }
    print (node->left);
    cout << "data :" << node->data << endl;
    print(node->right);
}

template <typename T>
void BST<T>::printInOrder()
{
   // cout << "BST::Test" << endl;
    print(root);
}

template <typename T>
void BST<T>::insert(Node* node, T data)
{
    
        if (data < node->data)
        {
            if (node->left == NULL)
                node->left = new Node(data);
            else
                insert(node->left, data);
        }
        else
        {
            if (node->right == NULL)
                node->right = new Node(data);
            else
                insert(node->right,data);
        }
   
    
}

template <typename T>
void BST<T>::insert(T data)
{
    if (root == NULL)
        root = new Node (data);
    else
    insert(root,data);
}

template <typename T>
bool BST<T>::Delete(Node* & node, T data)
{
    if (node == NULL)
    {
        return false;
    }
    else if ( data < node->data)
        Delete(node->left,data);
    else if (data > node->data)
        Delete(node->right, data);
    else
    {
        Node* temp;
        if (node->right == NULL)  // right child is NULL
        {
            temp = node->left;
            delete node;
            node = temp;
        }
        else if (node->left == NULL) // left child is NULL
        {
            temp = node->right;
            delete node;
            node = temp;
        }
        else
        {
			// Minimum of the right subtree and again delete the duplicate
            Node* min = node->right;
            while (min->left != NULL)
                min = min ->left;
            
            node->data = min->data;
            Delete (node->right, node->data);
            
        }
            
        
    }
        
}
template <typename T>
bool BST<T>::Delete(T data)
{
    return Delete(root,data);
}


#endif	/* BST_H */

