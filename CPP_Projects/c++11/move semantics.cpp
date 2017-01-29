#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class MemoryBlock
{
    size_t _length;
    int* _data;
    
public:
    
    // Simple constructor that initializes the resource.
    MemoryBlock(size_t len) : _length(len), _data(new int[_length])
    {
        std::cout << "In MemoryBlock(size_t). length = "
                << _length << "." << std::endl;
    }
    
    // Destructor.
    ~MemoryBlock()
    {
      std::cout << "In ~MemoryBlock(). length = "
                << _length << ".";
      
      if (_data != NULL)
      {
         std::cout << " Deleting resource.";
         // Delete the resource.
         delete[] _data;
      }

      std::cout << std::endl;
    }
    
   // Copy constructor.
   MemoryBlock(const MemoryBlock& other)
      : _length(other._length)
      , _data(new int[other._length])
   {
      std::cout << "In MemoryBlock(const MemoryBlock&). length = " 
                << other._length << ". Copying resource." << std::endl;

      std::copy(other._data, other._data + _length, _data);
   }

   // Copy assignment operator.
   MemoryBlock& operator=(const MemoryBlock& other)
   {
      std::cout << "In operator=(const MemoryBlock&). length = " 
                << other._length << ". Copying resource." << std::endl;

      if (this != &other)
      {
         // Free the existing resource.
         delete[] _data;

         _length = other._length;
         _data = new int[_length];
         std::copy(other._data, other._data + _length, _data);
      }
      return *this;
   }

   // Retrieves the length of the data resource.
   size_t Length() const
   {
      return _length;
   }  
   
   // Move Constructor.
   MemoryBlock(MemoryBlock&& other)
   {
       std::cout << "In MemoryBlock(MemoryBlock&&). length = " 
             << other._length << ". Moving resource." << std::endl;
       _data = other._data;
       _length = other._length;
       
       other._data = NULL;
   }
   
   // Move Assignment. 
   MemoryBlock& operator= (MemoryBlock&& other)
   {
       if (this != &other)
       {
           delete[] _data;
           _data = other._data;
           _length = other._length;
           
           other._data = NULL;
       }
       return *this;
   }
   
};

int main()
{
   // Create a vector object and add a few elements to it.
   vector<MemoryBlock> v;
   v.reserve(3);
   v.push_back(MemoryBlock(25));
   v.push_back(MemoryBlock(50));
   v.push_back(MemoryBlock(75));

  
}