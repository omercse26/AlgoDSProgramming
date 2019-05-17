#include<stdio.h>
#include<conio.h>
void main()
{
 int a[5][5] = {
		 {-1,10,-1,30,100},
		 {-1,-1,50,-1,-1},
		 {-1,-1,10,-1,100},
		 {-1,-1,-1,20,60},
		 {-1,-1,-1,-1,-1}
	       };
 int stack[100];
 int s=-1;
 int visited[5],n,i,count=0,t;
 clrscr();
 for(i=0;i<5;i++)
 {
   visited[i]='n';
   stack[i]=-1;
 }
 s++;
 stack[s] = 0;
 while(s>=0)
 {
  printf("stack :");
  for(i=0;i<5;i++)
   printf("%d ",stack[i]);
  printf("\n");
  n=stack[s];
  s--;
  while(1)
  {
   if(visited[n]=='y')
   {
    printf("visited :%d\n",n);
    break;
   }
   printf("%d\n",n);
   visited[n]='y';
   count=0;
   for(i=0;i<5;i++)
   {
    if(visited[i]=='n' && a[n][i]!=-1 && count==0)
    {
     count++;
     t=n;
     n=i;
     continue;
    }
    if(visited[i]=='n' && a[t][i]!=-1 && count!=0)
    {
     stack[++s]=i;
     printf("stacki :");
     for(i=0;i<5;i++)
       printf("%d ",stack[i]);
     printf("\n");
     break;
    }
   }

  }
 }
 getch();
}