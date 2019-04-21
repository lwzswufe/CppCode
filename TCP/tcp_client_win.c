#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdio.h>
#include <windows.h>
#include <winsock2.h> 
#include <ws2tcpip.h>

// gcc -g -Wall -lm tcp_client_win.c -o tcp_client.exe -lwsock32 -lws2_32
int main(int argc, char* argv[])
{
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data; 
    if(WSAStartup(sockVersion, &data) != 0)
    {
        return 0;
    }
 
    SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        printf("invalid socket !");
        return 0;
    }
    
    short port = 8888;
    char * IP = "127.0.0.1";
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(port);
    serAddr.sin_addr.S_un.S_addr = inet_addr(IP); 
    printf("connect address:%s:%d \r\n", IP, port);
    if (connect(sclient, (SOCKADDR *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        printf("connect error !");
        closesocket(sclient);
        return 0;
    }
    char * sendData = "TCP client: hello, TCP server!\n";
    send(sclient, sendData, strlen(sendData), 0);
 
    char recData[255];
    // 
    int ret = recv(sclient, recData, 255, 0);
    printf("ret:%d  strlength:%llu\n", ret, strlen(recData));
    if(ret > 0)
    {
        recData[ret] = 0x00;
        printf(recData);
    }
    closesocket(sclient);
    WSACleanup();
    return 0;
}
