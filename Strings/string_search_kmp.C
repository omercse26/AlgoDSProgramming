/*Q(i-j) and p(i-j,j) */
#include<stdio.h>
#include<conio.h>
#include<time.h>
void main()
{
 time_t t,e;
 char inp[]="aaaababaaaababcaa";
 char p[]="ababc";
 int fail[10],k,s,i=1,j;
 fail[0]=-1;
 clrscr();
 time(&e);
 for(k=1;k<strlen(p);k++)
 {
  i=1;
  //printf("finding for %d:\n",k);
  //getch();
  s=fail[k-1];
  while(s>=0)
  {
   //printf("%d:comparison between s:%d and k-1:%d for %d\n",i,s,k-1,k);
   if(p[s] == p[k-1])
    break;
   s = fail[s];
   //printf("\t assigned s:%d\n",s);
   i++;
  }
  fail[k] = s+1;

  }
 for(i=0;i<4;i++)
   printf("%d ",fail[i]);
 i=0;j=0;
 while(j < strlen(p) && i < strlen(inp))
 {
  while(j>=0 && inp[i] != p[j])
  {
    j=fail[j];
  }
   i=i+1;j=j+1;
 }
 printf("match found at %d\n",i-j);
 time(&t);
 printf("running time is %d",t-e);
 getch();
}