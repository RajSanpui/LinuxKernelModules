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
/* mmap maps a file into memory at a user given address. Advantage: Faster access, compared to a file write which reads/writes to disk
   disk access is slower than memory access, hence the advantage.
  
   map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        First field: Address at which to map the file. If 0, then system choses the address.
        2nd field: The protections given. (PROT_READ, PROT_WRITE, PROT_EXEC, (Pages may be read, write and executed.), PROT_NONE - Pages cannot be accessed.
        3rd field: MAP_ANONYMOUS - Not mapping a file. fd field is ignored. The map space initialized to 0.
        4th field: MAP_SHARED - Shared between processes.
        Last field: offset. Offset from where the file to map. 0 specifies from start
        
                   (For others see: https://man7.org/linux/man-pages/man2/mmap.2.html)
                   
                   Example for mapping file: 
                     
                      if ((src = mmap (0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == (caddr_t) -1)
                      {
                        printf ("mmap error for input");
                        return 0;
                      }
  
  References:
  https://www.linuxquestions.org/questions/programming-9/mmap-tutorial-c-c-511265/
  https://stackoverflow.com/questions/26259421/use-mmap-in-c-to-write-into-memory
  https://stackoverflow.com/search?q=user:575281+[mmap]
 */
