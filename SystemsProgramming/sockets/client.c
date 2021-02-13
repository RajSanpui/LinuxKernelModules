#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

#define PORT 555
void error(char *msg)
{
    perror(msg);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    char buffer[256];


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
        return 1;
    }


    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("Client: ERROR connecting to server");
        return 1;
    }

    strcpy(buffer, "Hello from client");
    n = write(sockfd, buffer,20);
    if (n < 0) {
         error("Client: ERROR writing to server socket");
    }

    bzero(buffer,256);
    n = read(sockfd,buffer,255);

    if (n < 0) {
         error("Client: ERROR reading from socket");
    }
    printf("Message from server: %s\n",buffer);
    return 0;
}
