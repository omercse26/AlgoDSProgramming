#include<stdio.h>
#include<conio.h>
int findpivot(int,int);
int partition(int,int,int);
void quick(int,int);
void swap(int,int);
int a[]={3,1,4,1,5,9,2,6,5,3};
struct stack
{
  int l;
  int r;
};
struct stack stack[100];
int s=-1;
void main()
{
 int i;
 clrscr();
 quick(0,9);
 for(i=0;i<10;i++)
   printf("%d\n",a[i]);
 getch();
}

void quick(int i,int j)
{
  int pivot,pivotindex,k;
  s++;
  stack[s].l=i;
  stack[s].r=j;
  //printf("adding: s:%d l:%d r:%d \n",s,i,j);
  while(s>=0)
  {
    i=stack[s].l;
    j=stack[s].r;
    //printf("deleting: s:%d l:%d r:%d \n",s,i,j);
    s--;
    while(1)
    {
       pivotindex = findpivot(i,j);
       if(pivotindex==-1)
       {
	  break;
       }
       pivot=a[pivotindex];
       k=partition(i,j,pivot);
       s++;
       stack[s].l=k;
       stack[s].r=j;
       //printf("adding: s:%d l:%d r:%d \n",s,k,j);
       j=k-1;
     }

   }
}

int findpivot(int i,int j)
{
 int firstkey;
 int k;
 firstkey = a[i];
 for(k=i+1;k<=j;k++)
 {
  if(a[k]>firstkey)
   return k;
  else if(a[k]<firstkey)
   return i;
 }
 return -1; // different keys were never found
}
int partition(int i,int j,int pivot)
{
 int l,r;
 l=i;
 r=j;
 while(l<=r)//while(l<r) think of this cos l==r is not possible
 {
  swap(l,r);
  while(a[l]<pivot)
   l++;
  while(a[r]>=pivot)
   r--;
 }
 return l;
}

void swap(int l,int r)
{
 int temp;
 temp = a[r];
 a[r] = a[l];
 a[l] = temp;
}