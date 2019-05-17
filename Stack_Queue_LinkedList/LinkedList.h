#pragma once
#include <memory>
#include <iostream>

template <typename T>
struct Node_t
{
	T data;
	Node_t* next;

	Node_t() : next(nullptr) { }
	Node_t(T a) : data(a), next(nullptr) {}

	~Node_t()
	{
		std::cout << "Deleted Node" << std::endl;
	}
};

template <typename TNode>
struct LinkedListIterator
{
	TNode* p;
	LinkedListIterator(TNode* p) : p(p) {}

	LinkedListIterator& operator++ ()
	{
		p = p->next;
		return *this;
	}

	bool operator != (const LinkedListIterator<TNode>& other)
	{
		return  p != other.p;
	}

	int operator*() { return p->data; }
};

template <typename T>
struct LinkedList
{
	//template <typename T>
	//using TNode = Node_t<T>;

	using iterator = LinkedListIterator<Node_t<T>>;

	std::unique_ptr<Node_t<T>> head;
	std::unique_ptr<Node_t<T>> last;

	LinkedList() : head(std::make_unique<Node_t<T>>()),
		last(std::make_unique<Node_t<T>>())

	{
		head->next = last.get();
	}

	void insert(T data)
	{
		auto temp = std::make_unique<Node_t<T>>(data);
		temp->next = head->next;
		head->next = temp.get();
		temp.release();
	}

	LinkedListIterator<Node_t<T>> begin()
	{
		auto t = LinkedListIterator<Node_t<T>>(head.get());
		return ++t;
	}
	LinkedListIterator<Node_t<T>>  end() { return LinkedListIterator<Node_t<T>>(last.get()); }

};
