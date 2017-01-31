#include<stdio.h>
#include "reciprocal.hpp"
int main(int argc,char **argv)
{
 int i;
 i=atoi(argv[1]);
 printf("the reciprocal %d is %f\n",i,reciprocal(i));
 return 0;
}

