#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// #pragma comment(lib, "ws2_32")  //手动连接编译wsock动态库 
// 编译时需要在exe后面加入参数 "-lwsock32", "-lws2_32"
// 在Settinngs里的coderunner里面加入:
// {"code-runner.executorMap": {"c": "cd $dir && gcc -g -Wall -lm $fileName -o $fileNameWithoutExt -lwsock32 -lws2_32 && $dir$fileNameWithoutExt"}}
// gcc -g -Wall -lm tcp_server_win.c -o tcp_server_win.exe -lwsock32 -lws2_32
#include <stdio.h>
#include <windows.h>
#include <winsock2.h> 
#include <ws2tcpip.h>
 
int main(int argc, char* argv[])
{
    //初始化WSA MAKEWORD(2,2) 意为sock版本2
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        return 0;
    }
 
    // 创建套接字
    // AF_INET表示32位IP地址 SOCK_STREAM 表示这个是连接的一个端点
    // family：协议族。常用的协议族有，AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等。
    // type：指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等。
    // protocol：指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }
 
    //绑定IP和端口
    short port = 8888;
    char * IP = "127.0.0.1";
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;               //  地址族  AF_INET表示32位IP地址
    sin.sin_port = htons(port);             //  端口号  htons是将整型变量从主机字节顺序转变成网络字节顺序
    //sin.sin_addr.S_un.S_addr = INADDR_ANY;  //  IP地址
    // net_addr()的功能是将一个点分十进制的IP转换成一个长整数型数（u_long类型）
    sin.sin_addr.s_addr = inet_addr(IP);
    // 填值的时候使用sockaddr_in结构，而作为函数的  参数传入的时候转换成sockaddr结构就行了
    printf("server address:%s:%d \r\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
    // sock_fd：socket描述字。
    // addr：struct sockaddr类型的数据结构，由于struct sockaddr数据结构类型不方便设置，所以通常会通过对truct sockaddr_in进行地质结构设置，
    // 然后进行强制类型转换成struct sockaddr类型的数据。
    // addr_len：对应的地址的长度。
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !");
    }
 
    //开始监听
    int BACKLOG = 1024;
    // conn_num：相应socket可以排队的最大连接个数。
    // sock_fd：socket描述字。
    // int listen(int sock_fd, int conn_num);
    if(listen(slisten, BACKLOG) == SOCKET_ERROR)
    {
        printf("listen error !");
        return 0;
    }
 
    //循环接收数据
    SOCKET sClient;
    struct sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr), revlen = 255;
    char revData[revlen]; 
    while (1)
    {
        printf("wait for connect...\n");
        // sock_fd：socket描述字。
        // client_addr：结果参数，用来接受一个返回值，这返回值指定客户端的地址，不需要可设置NULL。
        // addr_len：client_addr的长度。
        // int accept(int sock_fd, struct sockaddr *addr, socklen_t *addr_len); //返回连接描述字
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }
        // char *inet_ntoa (struct in_addr); 返回点分十进制的字符串在静态内存中的指针。
        printf("get a connect from:%s:%d \r\n", inet_ntoa(remoteAddr.sin_addr), ntohs(remoteAddr.sin_port));
        
        //接收数据
        int ret = recv(sClient, revData, revlen, 0);        
        if(ret > 0)
        {
            revData[ret] = 0x00;
            printf(revData);
        }
 
        //发送数据
        char * sendData = "TCP server: hello, TCP client!\n";
        // 第一个参数指定发送端套接字描述符；
        // 第二个参数指明一个存放应用程序要发送数据的缓冲区；
        // 第三个参数指明实际要发送的数据的字节数；
        // 第四个参数一般置0。
        send(sClient, sendData, strlen(sendData), 0);
        closesocket(sClient);
    }
    
    closesocket(slisten);
    WSACleanup();
    return 0;
}
