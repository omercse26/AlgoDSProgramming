#include<stdio.h>
#include<conio.h>
void main()
{
 int i,j,x,a[5],k;
 clrscr();
 for(i=0;i<5;i++)
  scanf("%d",&a[i]);

 for(i=1;i<5;i++)
 {
   x=a[i];
   //a[0]=x;
   j=i;
   while(x<a[j-1])
   {
    printf("\nj : %d\n",j);
    a[j] = a[j-1];j=j-1;
   }
   a[j]=x;
   printf("\niteration :%d\n",i);
   for(k=0;k<5;k++)
    printf("%d ",a[k]);
 }
 printf("\n");
 for(i=0;i<5;i++)
  printf("%d ",a[i]);
 getch();
}