#include<stdio.h>
#include<conio.h>
void main()
{
  int a[5],x,i,j,k;
  clrscr();
  for(i=0;i<5;i++)
    scanf("%d",&a[i]);
  for(i=0;i<4;i++)
  {
    x = a[i];
    k = i;
   for(j=i+1;j<5;j++)
   {
     if(a[j] < x)
     {
	 x=a[j];
	 k=j;
     }
   }
    a[k] = a[i];
    a[i] = x;
  }
  for(i=0;i<5;i++)
    printf("%d ",a[i]);
  getch();
}