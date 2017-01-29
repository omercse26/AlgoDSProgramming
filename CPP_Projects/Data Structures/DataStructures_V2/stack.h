#include "List.h"

template <typename T>
class Stack
{
	List<T> list;
public:
	void Push(T data)
	{
		list.insert(data);
	}

	T pop()
	{
		return list.removeFirst();
	}
};
