/* also called bubble sort*/
#include<stdio.h>
#include<conio.h>
void main()
{
  int a[5]={45,13,10,9,20},x,i,j,k;
  clrscr();
  for(i=0;i<5;i++)
    printf("%d\n",a[i]);
  for(i=1;i<=4;i++)  /* wrongly put i<4 and the impact is substantial*/
  {
   for(j=4;j>=i;j--)
   {
     if(a[j-1] > a[j])
     {
	 x=a[j];
	 a[j]=a[j-1];
	 a[j-1] = x;
     }
      for(k=0;k<5;k++)
	printf("iteration : %d index : %d  %d\n\n",j,i,a[k]);
      getch();
   }
   for(k=0;k<5;k++)
     printf("iteration : %d index : %d  %d\n",k,i,a[k]);
 }
  for(i=0;i<5;i++)
    printf("%d ",a[i]);
  getch();
}