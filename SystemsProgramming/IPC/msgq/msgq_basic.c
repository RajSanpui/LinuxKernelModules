#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} send, recv;

int main(int argc, char *argv[])
{
   int msqid;

   key_t key =67676; /* Alt: key_t key = ftok("shmfile",65); */

   /*  create the message queue: */
   if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
   }

   send.mesg_type = 1;
   recv.mesg_type = 1;

   /* Write to the message queue */
   strcpy(send.mesg_text, "Hello Message Queue !!\n");
  msgsnd(msqid, &send, sizeof(send), 0);

   /* Read from message queue */
   printf("Reading message queue.... \n");
   msgrcv(msqid, &recv, sizeof(recv), 1, 0);

   printf("Message received: %s",recv.mesg_text);

   /* Destroy the shared memory */
   msgctl(msqid, IPC_RMID, NULL);
}
