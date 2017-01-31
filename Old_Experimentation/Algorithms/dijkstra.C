#include<stdio.h>
#include<conio.h>
void main()
{
 int a[5][5] = {
		 {0,10,0,30,100},
		 {0,0,50,0,0},
		 {0,0,0,0,100},
		 {0,0,0,20,60},
		 {0,0,0,0,0}
	       };
  int s[5],d[5],t=0,i,j,k,temp,x,flag;
  clrscr();
  for(i=0;i<5;i++)
    s[i]=0;
  t++;
  for(i=0;i<5;i++)
    printf("%d ",s[i]);
  printf("\n");
  for(i=1;i<5;i++)
   d[i] = a[0][i];
  for(i=0;i<5;i++)
    printf("%d ",d[i]);
  printf("\n");
  for(i=0;i<4;i++)
  {
    x=-1;
    for(j=1;j<5;j++)
    {
      flag = 0;
      for(k=0;k<5;k++)
      {
       if(s[k]==j)
       {
	flag = 1;
	break;
       }
      }
      printf("flag:%d j:%d\n",flag,j);
      if(flag == 0 && d[j]!=0 && (x==-1 || d[j] < d[x]))
      {
       x=j;printf("in sub j:%d\n",j);
      }
    }
    s[t++] = x;
    printf("i:%d x:%d\n",i,x);
    for(j=0;j<5;j++)
    {
      flag = 0;
      for(k=0;k<5;k++)
      {
       if(s[k]==j)
       {
	flag = 1;
	break;
       }
      }
      if (flag == 0)
       if (d[j]!=0)
       {
	temp=d[x]+a[x][j];
	d[j] = d[j]<(a[x][j]==0?1000:temp)?d[j]:temp;
       }
       else
	if(d[x]+a[x][j]!=0)
	 d[j] = d[x]+a[x][j];
       printf("j = %d\n",d[j]);
    }
  }
  for(i=0;i<5;i++)
   printf("%d ",s[i]);
  printf("\n");
  getch();
}