#include<stdarg.h>
#include<assert.h>
#include<stddef.h>
#include<stdio.h>

#include "new.r"

void * new(const void* _class,...)
{
   const struct Class* class = _class;
   void *p = calloc(1,class->size);
   assert(p);
   * (const struct Class**) p = class;
   
   va_list ap;
   va_start(ap,_class);

   class->ctor(p,&ap);

   va_end(ap);

   printf("new : the size is %u\n",class->size);
   return p;
}

void delete (void * self)
{
  printf("why should we delete..\n");
  const struct Class ** cp = self;

  (*cp)->dtor(self);

  free(self);    
}

size_t sizeOf(const void * self)
{
        const struct Class * const * cp = self;
	assert(self && *cp );
	return (*cp)-> size;
}
