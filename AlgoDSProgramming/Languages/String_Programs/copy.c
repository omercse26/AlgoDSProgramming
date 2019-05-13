#include "syscalls.h"
int main()
{
  int a[10];
  while(read(0,a,10)>0)
    write(1,a,10);
  return 0;
}
