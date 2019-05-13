#include<pthread.h>
char **ptr;
void *thread(void *v);
int main()
{
 int i;
 pthread_t tid;
 char *message[2] = {
                      "Hello from foo",
                      "Hello from Bar"
                    };
 ptr = message;
 for(i=0;i<2;i++)
  pthread_create(&tid,NULL,thread,(void*)i);
 pthread_exit(NULL);
}

void *thread(void* v)
{
 int i = (int)v;
 static int count = 0;
 printf("[%d]: %s (cnt = %d)\n",i,ptr[i],++count);
}
  
