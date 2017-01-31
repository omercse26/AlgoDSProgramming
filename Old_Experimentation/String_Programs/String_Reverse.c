#include<stdio.h>
#include<string.h>
int main()
{
  char a[] = "omer asif";
  int i,j;
  int len = strlen(a);
  for (i=0,j=len-1;i<len/2;i++,j--)
  {
     printf("%c %c\n",a[i],a[j]);
     a[len] = a[i];
     a[i] = a[j];
     a[j] = a[len];
     
  }
  a[len] = '\0';
  printf("%s: \n",a);
  return 0;
}
