include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
        printf("Inside thread: Argument recvd %s",(char*)vargp);
}

int main()
{
        pthread_t tid;

        pthread_create(&tid, NULL, myThreadFun, "Hello Thread\n");
        pthread_join(tid, NULL);
        exit(0);
}
