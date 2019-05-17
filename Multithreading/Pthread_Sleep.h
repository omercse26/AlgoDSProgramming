#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
static pthread_cond_t var;
static pthread_mutex_t mtx;

void print()
{
	printf("woken up by the sleeper\n");
    fflush(stdout);
}

void* sleeper(void*)
{
	while(1)
	{
        Sleep(5000);
		pthread_cond_signal(&var);
	}
}	

int main()
{
		pthread_t thr;
		pthread_cond_init(&var, NULL);
		pthread_mutex_init(&mtx, NULL);
		pthread_create(&thr, NULL, sleeper, NULL);
		pthread_mutex_lock(&mtx);
		while(1)
		{
			/* atomically unlocks the mutex during wait */
			pthread_cond_wait(&var, &mtx);
			print();
		}
}