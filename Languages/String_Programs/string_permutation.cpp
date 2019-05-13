/* program to find permutation of a given string*/
#include<stdio.h>
#include<conio.h>
void rec(int);
void swap(int);
void swaplast(int);
int length;
char a[100];
long icount;
/*FILE *fp;  for writing into file  */
void main()
{
  clrscr();
  /*fp = fopen("per.txt","w"); open the file*/
  printf("enter the string \n");
  scanf("%s",a);
  while(a[++length] != '\0')
  {
  }
  printf("length : %d",length);
  printf("\n%ld %s\n",++icount,a);
  /*fprintf(fp,"\n%ld %s\n",icount,a); */
  rec(length);
  /*fclose(fp);*/
  getch();
}

/* recursive function to find the permuation*/
void rec(int i)
{
  if ( i<3)
  {
   swap(i);
   return;
  }
  /* if the current position is even */
  if (i%2 == 0)
  {
   /* first three iteration with swapping (length-i)th and length-(i+1)th character */
   for(int j=1;j<=2;j++)
   {
    rec(i-1);
    swap(i);
   }
   rec(i-1);
   /* other iterations with swapping (length-i)th and last character */
   swaplast(i);
   for(j=1;j<i-3;j++)
   {
    rec(i-1);
    swaplast(i);
   }
   rec(i-1);

  }
  /* if the current position is odd */
  else
  {
   /* all the  iterations with swapping (length-i)th and length-(i+1)th character */
   for(int j=1;j<i;j++)
   {
    rec(i-1);
    swap(i);
   }
   rec(i-1);
  }
}

/* to swap (length-i)th and length-(i+1) th character */
void swap(int i)
{
 char temp;
 temp = a[length-i+1];
 a[length-i+1] = a[length-i];
 a[length-i] = temp;
 printf("\n%ld %s\n",++icount,a);
 /*fprintf(fp,"\n%ld %s\n",icount,a); */
}

/* to swap (length-i)th and last  character */
void swaplast(int i)
{
  char temp;
  temp = a[length -1];
  for(int k=1;k<i;k++)
  {
   a[length-k] = a[length-k-1];
  }
  a[length-i] = temp;
  printf("\n%ld %s\n",++icount,a);
  /*fprintf(fp,"\n%ld %s\n",icount,a);  */
}



