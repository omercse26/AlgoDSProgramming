#include "Object.h"
int main()
{
  void *o = new(Object);
  delete(o);
  return o;
}
