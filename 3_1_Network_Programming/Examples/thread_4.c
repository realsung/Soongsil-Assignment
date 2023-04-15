#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *threadA_main(void *arg);
void *threadB_main(void *arg);

static int counter = 0;
static pthread_mutex_t mutex;

int main(int argc, char **argv)
{
	pthread_t thread_id_1, thread_id_2;
	int res;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&thread_id_1, NULL, threadA_main, NULL);
	pthread_create(&thread_id_2, NULL, threadB_main, NULL);
	pthread_join(thread_id_1, (void **) &res);
	pthread_join(thread_id_2, (void **) &res);
	
	pthread_mutex_destroy(&mutex);
	return 0;
}

void *threadA_main(void *arg)
{
	int i;
	for(i=0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		counter += 2;
		printf("Thread A increases the counter by 2: Counter - %d \n", counter);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *threadB_main(void *arg)
{
	int i;
	for(i=0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutex);
		counter += 3;
		printf("Thread B increases the counter by 3: Counter - %d \n", counter);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}




