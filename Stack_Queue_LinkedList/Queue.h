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
class Queue : private List <T>
{
	// Since empty does not have template parameter, ADL does not work.
	using List<T>::empty;
	using List<T>::front;
	using List<T>::removeFront;
	using List<T>::insertLast;


public:
	Queue() {}

	void enqueue(T data)
	{
		insertLast(data);
	}

	T dequeue()
	{
		try
		{
			if (empty())
			{
				throw "No Elements";
			}

			T temp = front();
			removeFront();
			return temp;
		}
		catch (const char* str)
		{
			std::cout << str << std::endl;
			throw;
		}
	}
};

void testdriver_queue()
{
	Queue<int> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);

	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.dequeue() << std::endl;
}

#endif	/* QUEUE_H */

