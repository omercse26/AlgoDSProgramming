/* 
 * File:   List.h
 * Author: omer.asif
 *
 * Created on January 24, 2013, 8:07 PM
 */

#ifndef LIST_H
#define	LIST_H
#include <iostream>
#include <memory>

//#include "List_Node.h"

using namespace std;

//template <typename T>
//class Iterator;

template <typename T>
struct ListNode
{
	T data;
	std::unique_ptr<ListNode> next;
	ListNode(T a) : data(a), next(nullptr) {}

	~ListNode()
	{
		cout << "Destructing node " << data << endl;
	}
};

template <typename T>
class List
{
	using Node = ListNode<T>;
	using NodePtr = std::unique_ptr<Node>;

	NodePtr root;
public:
	List() : root(nullptr) {}

	void insertFront(T data)
	{
		NodePtr node = std::make_unique<Node>(data);
		node->next = std::move(root);
		root = std::move(node);
	}

	NodePtr remove(T data)
	{
		Node* prev = nullptr;
		Node* curr = root.get();

		while (curr != nullptr)
		{
			if (curr->data != data)
			{
				prev = curr;
				curr = curr->next.get();
				continue;
			}

			if (curr != root.get())
			{
				auto temp = std::move(prev->next);
				prev->next = std::move(temp->next);
				return temp;
			}
			else
			{
				auto temp = std::move(root);
				root = std::move(temp->next);
				return temp;
			}
		}

		return nullptr;
	}

	void print()
	{
		for (Node* node = root.get(); node != nullptr; node = node->next.get())
		{
			cout << node->data << " ";
		}

		cout << endl;
	}
};

void testdriver() 
{	
	List<int> list;
	list.insertFront(1);
	list.insertFront(2);
	list.insertFront(3);

	list.remove(1);

	list.print();
}

//class List
//{
//protected:
//  typedef List_Node<T> Node;
//  Node *root;
//  
//public:  
//  List(): root (NULL) {};
//  ~List(){root->deleteAllNodes();}
//  
//  void insert(T);
//  Node* deleteNode(T);
//  void print();
//  Node* first() { return root; } 
//  Iterator begin() { return new Iterator(this); }
//};
//
//template <typename T>
//void List<T>::insert(T data)
//{
//   if (root == NULL)   
//      root = new Node(data);
//   else
//   {
//     root = new Node(data,root);
//   }
//}
//
//template <typename T>
//List_Node<T>* List<T>::deleteNode(T data)
//{
//   if (root == NULL)   
//      return NULL;
//   
//   Node *temp = root;
//   Node *prev = NULL;
//   while (temp)
//   {
//      if (temp->data == data)
//	  {
//		 if (temp == root)
//			root = temp->next;
//		 else
//			prev->next = temp->next;
//	         delete temp;
//		 return prev;
//	  }	  
//	  prev = temp;
//	  temp = temp->next;	     
//   }
//   return NULL;
//}
//
//template <typename T>
//void List<T>::print()
//{
//
//  for (Node *temp = root; temp != NULL; temp = temp->next)
//     cout << temp->data << " ";
//  cout << endl;
//}

#endif	/* LIST_H */

