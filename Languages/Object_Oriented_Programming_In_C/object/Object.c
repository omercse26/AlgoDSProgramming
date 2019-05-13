const void * classOf(const void * _self)
{
  const struct Object * self = _self;
  assert(self && self -> class);
  return self -> class;
}

size_t sizeOf (const void * _self)
{
  const struct Class * class = classOf(_self);
  return class->size;
}

static const struct Class object [] =
{

  { {object+1},
    "Object",object,sizeOf(struct Object),
    Object_ctor,Object_dtor
  }

  { {object+1},
    "Class",object,sizeof(struct Class),
    Class_ctor,Class_dtor
  }
};

const void * Object = object;
const void * Class  = object+1;

