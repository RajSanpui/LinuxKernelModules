/* Server which can accept upto 5 connections
   Receives client message and writes to client socket
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERV_PORT 555

void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
     int servsockfd, clientsockfd;
     char buffer[256];
     struct sockaddr_in serv_addr, client_addr;

     int n;

     servsockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (servsockfd < 0) {
        error("ERROR opening server socket");
        return 1;
     }


     serv_addr.sin_family = AF_INET; 
     //serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
     serv_addr.sin_port = htons(SERV_PORT);

     if (bind(servsockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
              error("ERROR on binding");
              return 1;
     }

     listen(servsockfd,5); // Upto 5 listeners


     while (1) 
     {
        int addrlen;
        addrlen=sizeof(client_addr);
        //clientsockfd = accept(servsockfd, (struct sockaddr *) &client_addr, (socklen_t *)sizeof(client_addr));
        clientsockfd = accept(servsockfd, (struct sockaddr *) &client_addr, &addrlen);
        if (clientsockfd < 0) {
           error("ERROR on accept client request");
        }

        n = read(clientsockfd,buffer,255);

        if (n < 0) {
         error("ERROR reading from socket");
        }

        printf("Here is the message: %s\n",buffer);
        n = write(clientsockfd,"Message received",20);
     }
     return 0; 
}
