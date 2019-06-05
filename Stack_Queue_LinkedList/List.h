#include <memory>
#include <iostream>

template <typename T>
class List
{
  
protected:
    class Node;
  	using OwningPtr = std::unique_ptr<Node>;
  
  	struct Node
	{
		T data;
		OwningPtr next;

		Node()    : data(),  next(nullptr) {}
		Node(T a) : data(a), next(nullptr) {}
		~Node()
		{
			std::cout << "Destructing Node " << data << std::endl;
		}
	};
  
    struct Iterator
    {
        // Non-owning pointer
        Node* p;
        Iterator(Node* p) : p(p) {}

        // Note: Pre-Increment
        Iterator& operator++ ()
        {
            p = p->next.get();
            return *this;
        }

        bool operator != (const Iterator& other)
        {
            return  p != other.p;
        }

        int operator*() { return p->data; }

        Node* operator -> () { return p; }

        operator Node*() { return p; }
    };  		    

	OwningPtr head_;

	// tail_ should be a non owning pointer since it will owned by some 'next' pointer,
	Node*   tail_;
  
    OwningPtr reverse(OwningPtr& currNodePtr)
    {
      	if (currNodePtr->next == nullptr)
        {
          	return std::move(currNodePtr);
        }
        
        auto copiedNxtPtr = currNodePtr->next.get();
        // This call will erase/move the currNodePtr->next
      	auto head = reverse(currNodePtr->next);
      
      	copiedNxtPtr->next = std::move(currNodePtr);
      
      	return head;
    }
  
  	OwningPtr& findNodeBefore(OwningPtr& head, Node* endPtr)
    {
       	if (head->next.get() == endPtr)
        {
          	return head;
        }
      
        return findNodeBefore(head->next, endPtr);
    }
  
    OwningPtr& findNodeBefore(Node* endPtr)
    {             
        return findNodeBefore(head_, endPtr);
    }
  
public:
	List() : head_(std::make_unique<Node>())	         
	{
		head_->next = std::make_unique<Node>();
		tail_ =  head_->next.get();
	}	
  
    Iterator begin() 
	{ 
		auto t = Iterator(head_.get()); 
		return ++t;
	}

	Iterator end() 
    { 
        return Iterator(tail_); 
    }

    void insertFront(T data)
	{
		OwningPtr node = std::make_unique<Node>(data);
		node->next = std::move(head_->next);
		head_->next = std::move(node);
	}
  
    void insertLast(T data)
    {
      	OwningPtr node = std::make_unique<Node>(data);      	
      	OwningPtr& nodeBeforeTail = findNodeBefore(tail_);      
        node->next = std::move(nodeBeforeTail->next);
        nodeBeforeTail->next = std::move(node);
    }
  
    void removeFront()
    {
        if (head_->next.get() == end()) { return; }
      
      	head_->next = std::move(head_->next->next);
    }
  
    void removeLast()
    {
      	OwningPtr& nodeBeforeTail = findNodeBefore(tail_);
      
        if (nodeBeforeTail.get() == begin()) { return; }
      
        OwningPtr& prevNode = findNodeBefore(nodeBeforeTail.get());            	
        prevNode->next = std::move(prevNode->next->next);
        
    }

	OwningPtr remove(T data)
	{
		auto prev = head_.get();
      
        for (auto itr = begin(); itr != end(); prev = itr, ++itr)
        {          
          	if (*itr == data)
            {
                // Take hold of curr owned by prev->next
              	auto tmp = std::move(prev->next);
				prev->next = std::move(itr->next);
				return tmp;
            }          		
        }		

		return nullptr;
	}
  
    void reverseList()
    {
      	auto headPtr = head_.get();
        head_ = reverse(head_);
      	tail_ = headPtr;
    }    
};

void testdriver() 
{	
	List<int> list;
	
  	for (int i = 1; i <= 10; ++i) { list.insertFront(i); }

	list.removeFront();
  
    list.removeLast();
  
  	list.insertLast(11);
  
    list.removeLast();
    
	for (const auto& i: list)
	{
		std::cout << i << std::endl;
	}
}
