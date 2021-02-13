
#include <stdio.h> 
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
 

sem_t myMutex; 

void* threadFunc(void* arg) 
{ 
	//wait 
	sem_wait(&myMutex); 
	printf("\nEntered critical section\n"); 

	//critical section 
	sleep(4); 
	
	// signal 
	printf("\n Exiting critical section...\n"); 
	sem_post(&myMutex); 
} 


int main() 
{ 
  // 2nd argument: 0 means shared betwn threads, non-zero means processes. 3rd arg specifies the initial sem value.
	sem_init(&myMutex, 0, 1); 
	pthread_t tid1, tid2;
  
	pthread_create(&tid1,NULL, threadFunc, NULL); 
	sleep(2); 
	pthread_create(&tid2, NULL, threadFunc, NULL);
  
	pthread_join(tid1, NULL); 
	pthread_join(tid2, NULL); 
	
        sem_destroy(&myMutex);
  
	return 0; 
} 
