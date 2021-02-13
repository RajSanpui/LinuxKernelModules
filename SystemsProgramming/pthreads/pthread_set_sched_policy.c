#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
        printf("Inside thread: I am %s",(char*)vargp);
}

int main()
{
        int ret;
        pthread_t tid;
        pthread_attr_t tattr;

        /* Initialize thread attribute */
        pthread_attr_init(&tattr);

        /* set the scheduling policy: 
           SCHED_OTHER 
           SCHED_FIFO 
           SCHED_RR 
        */
        ret = pthread_attr_setschedpolicy(&tattr, SCHED_OTHER);
        
        /* setting a new thread stack size */
        stacksize = (PTHREAD_STACK_MIN + 0x4000);
        ret = pthread_attr_setstacksize(&tattr, stacksize);

        pthread_create(&tid, &tattr, myThreadFun, "Thread1\n");

        pthread_join(tid, NULL);
        exit(0);
}
