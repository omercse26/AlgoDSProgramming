struct Object
{
    const struct Class * class;
};

struct Class
{
  const struct Object _;
  const char * name;
  const struct Class * super;
  size_t size;
  void * (*ctor) (void * self,va_list *app);
  void * (*dtor) (void * self);
};

void * new(const void * _class,...)
{
  const struct Class * class = _class;
  struct Object * object;
  va_list ap;
  
  assert(class && class->size);
  
  object = calloc(1,calloc->size);
  assert(object);
  object->class = class;
  va_start(ap,_class);
  object = ctor(object,&ap);
  va_end(ap);
  return(object);
}

void * ctor(void * _self,va_list * app)
{
  const struct Class * class = classOf(_self);
  assert(class->ctor);
  return class->ctor(_self,app);
}

void delete(void * _self)
{
  if(_self)
     free(dtor(_self));
}

void * dtor(void * _self)
{
  const struct Class * class = classOf(_self);
  assert(class->dtor);
  return class->dtor(_self);
}
  
  
