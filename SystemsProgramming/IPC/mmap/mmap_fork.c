#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int var = 100;  //global variable

int main(void)
{
    int *p;
    pid_t pid;

    int fd;
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    unlink("temp");  //Should work even w/o it. Delete the temporary file directory entry so that it can be released. This file is not necessary to exist. It is only used to complete the mapping area for communication between parent and child processes, so unlink.
    ftruncate(fd, 4);
    
    p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); // MAP_SHARED necessary to share betwn parent and child process. Else parent reads 0
    
    if(p == MAP_FAILED) {                
        perror("mmap error");
        exit(1);
    }
    close(fd);                   //After the mapping area is established, you can close the file

    pid = fork();                               //Create child process
    if(pid == 0){
        *p = 2000;
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);
        wait(NULL);

        int ret = munmap(p, 4);                 //Release map area
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    }

    return 0;
}
