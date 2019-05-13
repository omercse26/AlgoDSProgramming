#include<pthread.h>
void *thread(void *v);
int main()
{
 pthread_t tid;
 pthread_create(&tid,NULL,thread,NULL);
 pthread_join(tid,NULL);
 exit(0);
}

void *thread(void *v)
{
 printf("Hello World\n");
 return NULL;
}
