#include<pthread.h>
#include<stdio.h>

struct char_print_params
{
  char character;
  int count;
};

void *char_print(void* parameters)
{
  struct char_print_params* p = (struct char_print_params*) parameters;
  int i;
  
  for(i=0;i<p->count;i++)
    fputc(p->character,stdout);
  return NULL;
}

int main()
{
  pthread_t thread1_pid;
  pthread_t thread2_pid;
   
  struct char_print_params a,b;
  a.character = 'x';
  a.count = 1000;
  
  pthread_create(&thread1_pid,NULL,char_print,&a);

  // without join wont print anything
  pthread_join(thread1_pid,NULL);

  b.character = 'o';
  b.count = 2000;

  

  pthread_create(&thread2_pid,NULL,char_print,&b);
  pthread_join(thread2_pid,NULL);
  
  return 0;
}




  
