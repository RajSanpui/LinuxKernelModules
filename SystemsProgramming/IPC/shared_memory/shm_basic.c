#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

int main(int argc, char *argv[])
{
   int shmid;
   char *data;

   key_t key =67676; /* Alt: key_t key = ftok("shmfile",65); */
   /*  create the segment: */
   if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
   }

   /* attach to the segment to get a pointer to it: */
   data = shmat(shmid, NULL, 0);
   if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
   }
   
  /* Write to the shared memory */
   strcpy(data, "Hello Shared Memory !!");
   printf("Reading shared memory: %s \n",data);
}
