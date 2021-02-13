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

   /* Destroy the message queue */
   msgctl(msqid, IPC_RMID, NULL);
}

/* Message Type:
If msgtype is 0 − Reads the first received message in the queue

If msgtype is +ve − Reads the first message in the queue of type msgtype 
(if msgtype is 10, then reads only the first message of type 10 even though other types may be in the queue at the beginning)

If msgtype is –ve − Reads the first message of lowest type less than or equal to the absolute value of message type 
(say, if msgtype is -5, then it reads first message of type less than 5 i.e., message type from 1 to 5)
*/
