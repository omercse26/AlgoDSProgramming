#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char s[10000];
int flag;

void *producer (void *a)
{
  int i, j;
  flag = 0;
//  printf("Entering Producer:\n");
  pthread_mutex_lock (&mutex);
  for (i = 0; i < 10000; i++)
    {
      s[i] = 'p';
      for (j = 0; j < 10000; j++);
    }
//  printf("Producer: Sending Signal\n");
  pthread_mutex_unlock (&mutex);


 // printf("Exiting Producer:\n");
}

void *consumer (void *a)
{
  int i, j;


  flag = 1;
//  printf("Entering Consumer:\n");

//  printf("Consumer:Locking...\n");
  pthread_mutex_lock (&mutex);
  for (i = 0; i < 10000; i++)
    {
      s[i] = 'c';
      for (j = 0; j < 10000; j++);
    }
  pthread_mutex_unlock (&mutex);
//  printf("Exiting Consumer:\n");
}

int main ()
{
  pthread_t pid, cid;
  int corrupt, i;

  while (1)
    {
      pthread_create (&pid, NULL, producer, NULL);
      pthread_create (&cid, NULL, consumer, NULL);
      pthread_join (pid, NULL);
      pthread_join (cid, NULL);

      corrupt = 0;

      for (i = 0; i < 10000 - 1; i++)	{
  	if (s[i] != s[i + 1]){
	      corrupt = 1;
	      break;
	    }
      }


      if (corrupt)
		printf ("Memory is corrupted\n");
      else
		printf ("Not corrupted\n");

    }
  return 0;
}

