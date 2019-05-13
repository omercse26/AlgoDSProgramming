#include "String.h"
#include "new.h"
#include<stdio.h>
int main()
{
  void *a = new(String,"a");
  void *b = new(String,"b");
  //printf("sizeOf(a) == %u %u %u\n", a,*a,**a);
  delete(a);
  delete(b);
  return 0;
}
