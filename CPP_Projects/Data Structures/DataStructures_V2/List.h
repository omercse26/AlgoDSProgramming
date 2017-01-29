#include <iostream>
using namespace std;

template <typename T>
class List
{	
	struct Node
	{
		T data;
		Node* next;
		Node(const T other): data(other), next(0) {}
		~Node() {}

		void print()
		{
			cout << "data : " << data << endl;
		}	
	};
	static Node NullNode;

	Node* first;
	Node* last;

public:
	List() : first(0), last(0) {}

	void insert(T data)
	{
		Node * new_node = new Node(data);
		new_node->next = first;
		first = new_node;
		if (!last) last = new_node;
	}

	void insertLast(T data)
	{
		Node* new_node = new Node(data);
		if (last) last->next = new_node;
		last = new_node;
		if (!first) first = new_node;
	}

	T removeFirst()
	{
		Node* temp = first;
		T temp_data = temp? temp->data:0;
		if (first) first = first->next;
		if (first == 0) last = 0;
		delete temp;
		return temp_data;
	}

	void insertinorder(T data)
	{
		Node * new_node = new Node(data);
		
		if (first == 0)
			first = new_node;
		else
		{
			Node *i = first, *prev = 0;
			for (; i!=0 && i->data < data; prev=i,  i=i->next) {}
			prev->next = new_node;
			new_node->next = i;
		}	
	}

	void remove(T data)
	{
		Node* prev = 0, *i = first;
		
		for (; i!=0 && i->data != data ;prev=i,i=i->next){}

		if (i == 0)
			cout << "Element Not Found" << endl;
		else
		{
			prev ? prev->next = i->next : first=i->next;
			delete i;			
		}	
	}

	~List()
	{
		for (Node* i=first; i != 0;)
		{
			Node* curr = i;
			i=i->next;
			cout << "Destructing " << curr->data << endl;
			delete curr;
		}
		first = 0;
		last = 0;
	}

	void print()
	{
		for (Node* i=first; i != 0;i=i->next)
                {
			cout << i->data << ":" ;
                }
		cout << endl;
	}
};		

template <typename T>
typename List<T>::Node List<T>::NullNode = Node(0);
