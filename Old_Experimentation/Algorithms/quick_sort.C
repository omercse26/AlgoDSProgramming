/* algorithm by aho,hopcroft */
/* the core function is partition */
#include<stdio.h>
int findpivot(int,int);
int partition(int,int,int);
void quick(int,int);
void swap(int,int);
int a[]={3,1,4,1,5,9,2,6,5,3};
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
 pivotindex = findpivot(i,j);
 if (pivotindex >= 0)
 {
  pivot = a[pivotindex];
  k = partition(i,j,pivot);
  printf("i=%d j=%d k=%d pivot = %d\n",i,j,k,pivot);
  quick(i,k-1);
  quick(k,j);
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
