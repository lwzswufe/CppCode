#include <stdio.h>
#include <winsock2.h> 
#include <windows.h>

/*
发送数据要根据HTTP协议的要求附加协议头：
static const char* protocolHead=
"GET http://www.xxx.com/index.html HTTP/1.1/n"
"Accept: image/gif, image/x-xbitmap, image/jpeg,/n"
"Accept-Language: zh-cn/n"
"User-Agent:iPanelBrowser/2.0/n"
"Host: www.xxx.com:80/n"
"Connection: close/n/n"
*/
int main()
{
WSADATA wsaData;
SOCKET Socket;
SOCKADDR_IN SockAddr;
struct hostent *host;
char buffer[10000];
int nDataLength;
char * website_HTML;

// website url
char * website = "tool.bitefu.net";
char * sendurl = "http://tool.bitefu.net/jiari/?d=20180101&back=json";
// char * code = "sz399001";

//HTTP GET
char get_http[256];
sprintf(get_http, "GET %s HTTP/1.1\r\nHost: %s \r\nConnection: close\r\n\r\n", sendurl, website);
// sprintf(get_http, "HEAD / HTTP/1.1\r\nHost: %s \r\nConnection: close\r\n\r\n", url);
// sprintf(get_http, "GET / HTTP/1.1\r\nHost: hq.sinajs.cn/list=s_%s \r\nConnection: close\r\n\r\n", code);
printf(get_http);


    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        printf("WSAStartup failed.\n");
        //system("pause");
        return 1;
    }
    printf("connect success\n");

    Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    host = gethostbyname(website);

    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    printf("url address:%s\n", inet_ntoa(SockAddr.sin_addr));
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        printf("Could not connect");
        //system("pause");
        return 1;
    }

    // send GET / HTTP
    send(Socket, get_http, strlen(get_http), 0);

    // recieve html
    while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0)
    {        
        // int i = 0;
        website_HTML = buffer;
        // while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
        // {
        //     website_HTML+=buffer[i];
        //     i += 1;
        // }               
    }

    closesocket(Socket);
    WSACleanup();

    // Display HTML source 
    printf(website_HTML);

    // pause
    printf("\n\nPress ANY key to close.\n\n");
return 0;
}
