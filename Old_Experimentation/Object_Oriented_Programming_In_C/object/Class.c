static void * class_dtor(void * _self)
{
   struct class * self = _self;
   fprintf(stderr,"%s: cannot destroy class\n",self->name);
   return 0;
}

const void * super(const void * _self)
{
   const struct Class * self = _self;
   assert(self,self->super);
   return self->super;
}

static void * Class_ctor(void * _self,va_list *app)
{
  struct class * self = _self;
  self->name = va_arg(*app,char*);
  self->super = va_arg(*app,struct Class *);
  self->size = va_arg(*app,size_t);
  assert(self->super);

  const size_t offset = offsetof(struct Class,ctor);
  memcpy((char *)self+offset,(char *) self -> super+offset,sizeOf(self->super)-offset);
  
  while((selector = va_arg(ap,voidf)))
  {
     voidf method = va_arg(ap,voidf);
     
     if (selector == (voidf) ctor)
         *(voidf*) & self->ctor = method;
     else if (selector == (voidf)dtor)
         *(voidf*) & self->dtor = method;
  }
  return self;
}
