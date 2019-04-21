/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n, buffer_size = 256;
    char buffer[buffer_size];
    uint32_t server_ip;
    if (argc < 2)
    {
        // fprintf(stderr,"ERROR, no port provided\n");
        // exit(1);
        portno = 8888;
        server_ip = inet_addr("127.0.0.1");
    }
    else
    {
        portno = atoi(argv[2]);
        server_ip = inet_addr(argv[1]);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_addr.s_addr = server_ip;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    printf("server address %s:%d \r\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");

    n = write(newsockfd,"hello I'm Server", 18);
    if (n < 0) 
        error("ERROR writing to socket");

    bzero(buffer, buffer_size);
    n = read(newsockfd,buffer, buffer_size);
    if (n < 0) 
        error("ERROR reading from socket");
        
    close(newsockfd);
    close(sockfd);
    return 0; 
}