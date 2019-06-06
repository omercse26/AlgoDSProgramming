/* 
 * File:   Stack.h
 * Author: omer.asif
 *
 * Created on January 25, 2013, 2:52 PM
 */

#ifndef STACK_H
#define STACK_H

#include "List.h"

template <typename T>
class Stack
{
    List<T> list;

public:
    void push(T data)
    {
        list.insertLast(data);
    }

    T pop()
    {
        auto temp = list.back();
        list.removeLast();
        return temp;
    }
};

void testdriver_stack()
{
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
}

#endif    /* STACK_H */

