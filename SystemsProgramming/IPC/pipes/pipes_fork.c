include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int pid, fd[2], status;
  char rd[30];

  if(pipe(fd) == -1)
    perror("Pipe");

  pid = fork();
  if (!pid)
  {
    write(fd[1], "Hello, from child\n",19);
  }

  if (pid>0)
  {
    sleep(1); // To make sure child gets a chance first
    read(fd[0], rd, 19);
    printf("Parent - Message read: %s",rd);

    waitpid(pid, &status, 0);
  }

}
