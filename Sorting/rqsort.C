#include<stdio.h>
#define MAX 6
void qsort(FILE*,int[],int,int);
void main()
{
	FILE *fp = fopen("output","w");
	int a[]={3,5,4,6,2,1},i;
	clrscr();
	for(i=0;i<MAX;i++)
	   fprintf(fp,"%d%c",a[i],(i!=MAX-1?' ':'\n'));
	//printf("\n");
	qsort(fp,a,0,MAX-1);
	for(i=0;i<MAX;i++)
	  fprintf(fp,"%d\n",a[i]);
	fclose(fp);
	getch();
}


/* qsort: sort v[left]...v[right] into increasing order */
void qsort(FILE *fp,int v[], int left, int right)
{
   int i, last,j;//last is the indicator for the last found minimum value
   void swap(int v[], int i, int j);
   fprintf(fp,"\n\n");
   if (left >= right) /* do nothing if array contains */
       return; /* fewer than two elements */
   swap(v, left, (left + right)/2); /* move partition elem */
   last = left; /* to v[0] */
   fprintf(fp,"bpart:left:%d right:%d lst:%d swapped:(%d,%d)\n",left,right,last,left,(left + right)/2);
   for(j=0;j<MAX;j++)
	   fprintf(fp,"%d ",v[j]);
   fprintf(fp,"\n");
   for (i = left + 1; i <= right; i++) /* partition */
      if (v[i] < v[left])
      {
	 swap(v, ++last, i);
	 fprintf(fp,"  ipart:left:%d i:%d lst:%d swapped:(%d,%d)\n",left,i,last,i,last);
	 for(j=0;j<MAX;j++)
	   fprintf(fp,"  %d ",v[j]);
	 fprintf(fp,"\n");
      }
   fprintf(fp,"apart:left:%d right:%d lst:%d\n",left,right,last);
   for(j=0;j<MAX;j++)
	   fprintf(fp,"%d ",v[j]);
   fprintf(fp,"\n");
   swap(v, left, last); /* restore partition elem */
   fprintf(fp,"rpart:left:%d right:%d lst:%d swapped:(%d,%d)\n",left,right,last,left,last);
   for(j=0;j<MAX;j++)
	   fprintf(fp,"%d ",v[j]);
   fprintf(fp,"\n");
   qsort(fp,v, left, last-1);
   qsort(fp,v, last+1, right);
}
/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
  int temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}