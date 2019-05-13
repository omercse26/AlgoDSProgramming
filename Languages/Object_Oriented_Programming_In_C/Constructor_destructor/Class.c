#include<stdarg.h>
#include<assert.h>
#include<stddef.h>
struct Class
{
   size_t size;
   void * (*ctor) (void* self,va_list* app);
   void * (*dtor) (void* self);
   void * (*clone) (const void * self);
   int  * (*differ) (const void *self,const void* b);

};

void * new (const void * _class,...)
{
	const struct Class* class = _class;

	void * p = calloc(1,class->size);
	assert(p);
	*(const struct class **)p=class;

	if (class -> ctor)
	{
		va_list ap;

		va_start(ap,_class);

		p = class -> ctor(p,&ap);

		va_end(ap);
	}

	return p;
}

void delete (void * self)
{
	const struct Class ** cp = self;

	if (self && *cp && (*cp)->dtor)
		self = (*cp) -> dtor(self);
	free(self);
}

int differ(const void * self,const void * b)
{
	const struct Class * const * cp = self;
	assert(self && *cp && (*cp) ->differ);
        return (*cp)-> differ(self,b);
}

size_t sizeOf(const void * self)
{
   const struct Class * const * cp = self;

	assert(self && *cp );
	return (*cp)-> size;
}
