/* 
 * File:   BinaryHeap.h
 * Author: omer.asif
 *
 * Created on January 28, 2013, 7:22 PM
 */

#ifndef BINARYHEAP_H
#define	BINARYHEAP_H

template <typename T, typename Compare>

class BinaryHeap
{
	vector<T> ele;
	int curr;        
    Compare compare;
	
	int parent(int k) { return k/2; }
	int leftChild(int k);
	int rightChild(int k);
	void heapify();
	void percolateDown();
	
public:
	Heap(Compare func): curr(1),compare(func) 
	{
		ele.reserve(100);
	}            
	
	void insert(T a)
	{
	   ele[curr] = a;
	   heapify();
	   curr++;
	}
	
	 T deleteMax()
     {
        T max = ele[1];
        ele[1] = ele[--curr];     
        percolateDown();
        return max;
     }
};	 
	
template <typename T>	
int BinaryHeap<T>::leftChild(int k) 
{ 
	  int left = k*2;
	  
	  if (left > curr) // Check if there is valid left child
		return 0;      // '0' is OK since we dont store at zero
		
	  return left; 
}

template <typename T>
int BinaryHeap<T>::rightChild(int k) 
{ 
      int right = (k*2)+1;
	  
      if (right > curr) // Check if there is valid left child
			return 0;
			
      return right; 
}
	
template <typename T>	
void BinaryHeap<T>::heapify()
{
		int current = curr;
		while (current > 1) 
		{ 
			// compare current node with its parent.
            if ( compare(ele[current], ele[parent(current)]) )
			{
				// if true swap
				T temp = ele[current];
				ele[current] = ele[parent(current)];
				ele[parent(current)] = temp;
				
				current = parent(current);
			}	
			else
			{
				return;
			}
		}
}
        
template <typename T>		
void BinaryHeap<T>::percolateDown()
{
    int first = 1;
            
    while(1)
    {
       if (  	leftChild(first)  // there is valid left child
				// Left child is 'greater' than the right child
                && compare ( ele[leftChild(first)], ele[rightChild(first)] ) 
				// Child is greater so swap
				&& compare ( ele[leftChild(first)], ele[first] )
		  )                    
          {
                    T temp = ele[first];
                    ele[first] = ele[leftChild(first)];
                    ele[leftChild(first)] = temp;
                    first = leftChild(first);
          }
                
       else if (rightChild(first) // else check the right child
                   && (compare(ele[rightChild(first)],ele[first] ))
			)                    
                {
                    T temp = ele[first];
                    ele[first] = ele[rightChild(first)];
                    ele[rightChild(first)] = temp;
                    first = rightChild(first);
                }
       else
               return;
     }
                        
}        
#endif	/* BINARYHEAP_H */

