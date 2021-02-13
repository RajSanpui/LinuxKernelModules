#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int global = 100;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThreadFun(void *vargp)
{
        printf("Inside thread: I am %s \n",(char*)vargp);
        pthread_mutex_lock(&mutex);
        printf("thread: %s acquired lock. \n",(char*)vargp);

        global++;

        printf("thread: %s releasing lock.  \n",(char*)vargp);
        pthread_mutex_unlock(&mutex);

}

int main()
{
        pthread_t tid1, tid2;

        pthread_create(&tid1, NULL, myThreadFun, "Thread1");
        pthread_create(&tid2, NULL, myThreadFun, "Thread2");

        while(1);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        exit(0);
}
