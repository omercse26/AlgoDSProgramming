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
      
        while (!queue.empty())
        {
            temp.enqueue(queue.dequeue());
        }
    
        queue.enqueue(data);

        while (!temp.empty())
        {
            queue.enqueue(temp.dequeue());
        }
    }

    T pop()
    {
        return queue.dequeue();
    }
};

void testdriver_stackqueue()
{
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
}
