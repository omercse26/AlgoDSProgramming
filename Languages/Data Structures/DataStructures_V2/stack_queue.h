#include "Queue.h"

template <typename T>
class Stack
{
	Queue<T> queue;
	Queue<T> temp;
public:
	void push(T data)
	{
		T temp_data;
		while ( temp_data=queue.dequeue())
			temp.enqueue(temp_data);
	
		queue.enqueue(data);

		while ( temp_data = temp.dequeue())
			queue.enqueue(temp_data);
	}

	T pop()
	{
		return queue.dequeue();
	}
};
