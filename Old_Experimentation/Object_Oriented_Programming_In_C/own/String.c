#include<stdarg.h>
#include<string.h>
#include<stddef.h>
#include "new.r"
struct String
{
   const void * class;
   char * text;
};

static void * String_ctor (void * _self,va_list* app)
{
    struct String * self = _self;  
    const char * text = va_arg(*app,const char *);
    self->text = malloc(strlen(text+1));  
    strcpy(self->text,text);
    return self;
}

static void * String_dtor(void * _self)
{

    struct String * self = _self;   
    printf("str dtor : %s\n",((struct String *) _self)->text);
    free(self->text);
    printf("str dtor : %s\n",((struct String *) _self)->text);
    self->text = 0;
    printf("str dtor : %s\n",((struct String *) _self)->text);
    return self;
}

static const struct Class _String =
{
   sizeof(struct String),
   String_ctor,
   String_dtor
};

const void * String = &_String;
