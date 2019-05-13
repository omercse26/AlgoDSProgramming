#include <iostream>
using namespace std;

template <typename T>
class List
{
	template <typename U>
	struct INode
	{
		U data;
		INode<U>* prev;
		INode<U>* next;

		INode(U data) : data(data), prev(0), next(0) {}
		~INode() {}
		void print() { cout << data << " "; }
	};

	template <typename U>
	struct INode <U*>
	{
                U* data;
                INode<U*>* prev;
                INode<U*>* next;

                INode(U* data) : data(new U(*data)), prev(0), next(0) {}
                ~INode() 
		{
			delete data;	
			data = 0;
		}
                void print() { cout << data << " "; }
        };

	typedef INode<T> Node;

	Node* first;	
	Node* last;

public:
	List():first(0), last(0) {}

	~List()
	{
		for (Node* curr = first; curr!=0;)
		{
			Node* temp = curr->next;
			delete curr;
			curr = temp;
		}
		first = 0;
		last  = 0;
	}

	void insert(T data)
	{
		Node* new_node = new Node(data);
		new_node->next = first;
		if (first) {first->prev = new_node;}
		first = new_node;
		if (!last) { last = first;}
	}

	void remove(T data)
	{
		Node *curr = first;
		for (; curr!=0 && curr->data!=data; curr=curr->next) {}
		if (curr)
		{
			if (curr!=first && curr!=last)
			{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				delete curr;
			}
			else if ( curr == first)
			{
				first = curr->next;
				first->prev = 0;
				delete curr;
			}
			else if ( curr == last)
			{
				last = curr->prev;
				last->next = 0;
				delete curr;	
			}
		}
		else
		{
			cout << "Element Not Found" << endl;
		}
	}	

	void print()
	{
		for (Node* curr = first; curr!=0; curr=curr->next)
			curr->print();

		cout << endl;
		cout << "Now Reverse Traversal" << endl;

		for (Node* curr = last; curr!=0; curr=curr->prev)
			curr->print();

		cout << endl;
	}
			

};
