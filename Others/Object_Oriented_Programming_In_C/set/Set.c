#include<assert.h>
#include<stdio.h>
#if ! defined MANY || MANY < 1
#define MANY 10
#endif

static int heap [MANY];

const void * Set;
const void * Object;

void * new (const void * type, ...)
{

	int * p= heap + 1; /* & heap[1..] */
	/*printf("Pointer %u\n",p);*/
	printf("Heap %u\n",heap);
	/*printf("Heap %u\n",heap+MANY);*/
    for (p = heap + 1; p < heap + MANY; ++p)
	{
		 printf("Pointer value %u\n",*p);
         if (! *p)
           break;
		 //printf("Pointer %u\n",p);
	}
    assert(p < heap + MANY);
    *p = MANY;
	printf("Pointer %u\n",p);
	/*printf("%u\n",MANY);*/
    return p;
}


void delete (void * _item)
{
	int * item = _item;
    if (item)
    {
		assert(item > heap && item < heap + MANY);
        * item = 0;
    }
}

void * add (void * _set,const void * _element)
{
   int * set = _set;
   const int * element = _element;

   assert(set > heap && set < heap+MANY);
   assert(*set ==  MANY);
   assert(element > heap && element < heap+MANY);
   printf("add:Set %u\n",set);printf("add:Heap %u\n",heap);
   if (*element == MANY)
      * (int *) element = set - heap;
   else
      assert(*element == MANY);

   printf("add:Element %d\n",*(int *)element);
   return (void *) element ;

}

void * find (const void * _set,const void * _element)
{
	const int * set = _set;
    const int * element = _element;

    assert(set > heap && set < heap+MANY);
    assert(*set ==  MANY);
    assert(element > heap && element < heap+MANY);
    assert(*element);

    return *element == set - heap ? (void *) element :0;
}

int contains (const void * _set,const void * _element)
{
   return find(_set,_element)!=0;
}

void * drop (void * _set,const void * _element)
{
	int *element = find(_set,_element);
	if (element)
	   *element = MANY;
	return element;
}

int differ(const void *a,const void *b)
{
	return a != b;
}