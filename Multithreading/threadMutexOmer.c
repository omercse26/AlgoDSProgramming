#include <pthread.h>
#include <stdio.h>

char shared[10000];

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* producer (void* a)
{
	int i,j;

	pthread_mutex_lock(&mutex);
	for (i=0; i<10000-1; i++)
	{
		shared[i]='p';
		for(j=0;j<10000;j++) ;		
	}
	shared[i] = '\0';

	pthread_mutex_unlock(&mutex);
}


void* consumer(void* a)
{
	int i,j;

	pthread_mutex_lock(&mutex);
	for (i=0; i<10000-1; i++)
        {
        	shared[i]='c';
		for(j=0;j<10000;j++) ;		
	}
	shared[i] = '\0';

	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t pid;
	pthread_t cid;
	int count=0, corrupt, i;

	pthread_mutex_init(&mutex,NULL);


	int j=0;
	while(j<10) {
		pthread_create(&pid, NULL, producer, NULL);
		pthread_create(&cid, NULL, consumer, NULL);
		pthread_join(pid, NULL);
		pthread_join(cid, NULL);	

		corrupt = 0;

		for (i=1; i<10000-1; i++)
		{
			if (shared[i] != shared[i-1])
			{
				corrupt = 1;
				break;
			}
		}

		if (corrupt)
			printf("Memory corruption happened: %d\n", count);
		else
			printf("Coding is fun...No corruption\n");
			
		count++;
		j++;
	}

}

