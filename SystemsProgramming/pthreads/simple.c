#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
        printf("Inside thread: I am %s",(char*)vargp);
}

int main()
{
        pthread_t tid1, tid2;

        pthread_create(&tid1, NULL, myThreadFun, "Thread1\n");
        pthread_create(&tid2, NULL, myThreadFun, "Thread2\n"); // The last argument is optional can be NULL
        
        pthread_join(tid11, NULL);
        pthread_join(tid12, NULL);
        
        exit(0);
}
