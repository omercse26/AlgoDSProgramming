#ifndef PQUEUE_H
#define	PQUEUE_H

#include "BinaryHeap.h"
template <typename T>
class PQueue
{
public:
        
    struct Data
    {
        T value;
        int key;    
        Data(T a,int b): value(a),key(b) {}
    };
    
    int count;
    
    static bool compare2 (Data a,Data b)
        {
            return ( a.key < b.key);
        }
    
    BinaryHeap<Data, bool (*)(Data,Data)> *heap;
    
    PQueue()
    {
        heap = new BinaryHeap<Data, bool (*)(Data,Data)>((PQueue::compare2));
        count = 0;
    }
    
    void enqueue(T value, int key)
    {
        heap->insert(Data(value,key)); count++;
    }
    
    T deque()
    {
        Data data = heap->deleteMax();
        count--;
        return data.value;        
    }
       
};

#endif

