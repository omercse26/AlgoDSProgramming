#include "List.h"

template <typename T>
class Queue
{
	List<T> list;
	
public:

	void enqueue(T data)
	{
		list.insertLast(data);
	}

	T dequeue()
	{
		return list.removeFirst();		
	}

	void print()
	{
		list.print();
	}
};		
