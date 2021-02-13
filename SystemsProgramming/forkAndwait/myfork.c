#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
  int pid;
  int status;
  pid = fork();

  if (!pid) // child process as pid = 0
  {
    printf("Child process: PID = %u, parent: %u\n", getpid(), getppid());
    execlp("ls", "-l", NULL);

    printf("This will not get printed");
  }
  if (pid > 0)
  {
    printf("This is parent process. PID: %u \n", getpid());
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
            printf("Child process exited gracefully \n");
    if (WIFSIGNALED(status))
            printf("Child process exited due to signal \n");
    if (WIFSTOPPED(status))
            printf("Child process stopped \n");
  }
}
