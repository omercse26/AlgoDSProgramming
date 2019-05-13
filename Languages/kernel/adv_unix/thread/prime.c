#include<pthread.h>
#include<stdio.h>

void* compute_prime(void* arg)
{
  int candidate = 2;
  while (1)
  {
    int factor;
    int is_prime = 1;
    
    for(factor=2;factor<candidate;factor++)
    {
      if(candidate % factor == 0)
      {
         is_prime = 0;
         break;
      }
    }

    if(is_prime)
    {
      
