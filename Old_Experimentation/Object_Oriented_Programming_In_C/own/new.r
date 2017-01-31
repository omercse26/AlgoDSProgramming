#include<stddef.h>
struct Class 
{
   size_t size;
   void * (*ctor) (void *self,va_list *app);
   void * (*dtor) (void *self);
};
