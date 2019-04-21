#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) 
    {
        // fprintf(stderr,"usage %s hostname port\n", argv[0]);
        // exit(0);
        portno = 8888;
        server = gethostbyname("127.0.0.1");
    }
    else
    {
        portno = atoi(argv[2]);
        server = gethostbyname(argv[1]);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    printf("server address %s:%d \r\n", server->h_name, ntohs(serv_addr.sin_port));

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    printf("connect successful\n");
    
    n = read(sockfd,buffer,255);                    // recv data
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    bzero(buffer,256);
    sprintf(buffer, "Hello I'm Client");
    n = write(sockfd,buffer,strlen(buffer));        // send data
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    
    close(sockfd);
    return 0;
}