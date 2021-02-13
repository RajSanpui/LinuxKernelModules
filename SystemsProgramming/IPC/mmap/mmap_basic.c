#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    void *ptr;

    ptr=mmap(NULL, 10, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
    strcpy(ptr, "Hello");
    printf("Reading mmap: %s",(char*)ptr);

    if(munmap(ptr, 10) == -1)
            perror("munmap");

}
/*
 * References:
 * https://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
 * https://stackoverflow.com/questions/26259421/use-mmap-in-c-to-write-into-memory
 * https://stackoverflow.com/search?q=user:575281+[mmap]
 */
