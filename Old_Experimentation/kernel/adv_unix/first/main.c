#include<stdio.h>
/* #include<stdlib.h> */
/* #include "reciprocal.h" */
double reciprocal(int);
int main(int argc,char **argv)
{
 int i;
 i=atoi(argv[1]);
 printf("the reciprocal %d is %f\n",i,reciprocal(i));
 return 0;
}

double reciprocal(int i)
{ 
 return 1.0/i;
}
