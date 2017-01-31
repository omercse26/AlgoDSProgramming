#include<stdio.h>
#include<conio.h>
void main()
{
  int a[100],b[100],i=0,j;
  unsigned long y = 40, z = 50, sum = 0,delta = 0x9e3779b9 ; /* a key schedule constant */
  long k[4]={12,13,14,15};
  clrscr();
  printf("y: %u z:%u\n",y,z);
  while(y>0)
  {
     a[i++]=y%2;
     y/=2;
  }
  for(j=i-1;j>=0;j--)
    printf("%d",a[j]);
  printf("\n");
  i=0;

  while(z>0)
  {
       b[i++]=z%2;
       z/=2;
  }
  for(j=i-1;j>=0;j--)
    printf("%d",b[j]);
  printf("\n");
  y=40;z=50;
  sum += delta ;
  y += ((z<<4)+k[0]) ^ (z+sum) ^ ((z>>5)+k[1]) ;
  z += ((y<<4)+k[2]) ^(y+sum) ^((y>>5)+k[3]) ; /* end cycle */

  printf("y: %u z: %u\n",y,z);
  i=0;
  while(y>0)
  {
     a[i++]=y%2;
     y/=2;
  }
  for(j=i-1;j>=0;j--)
    printf("%d",a[j]);
  printf("\n\n");

  i=0;

  while(z>0)
  {
       b[i++]=z%2;
       z/=2;
  }
  printf("%d\n",i-1);
  for(j=i-1;j>=0;j--)
    printf("%d",b[j]);
  printf("\n\n");
}




