#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <stdexcept>
using std::runtime_error;
#define TCP_BUFFER_SIZE 1024

class TCPError :public runtime_error
{
public: TCPError(const std::string &s) : runtime_error(s) 
{   
    try
    {
    perror(s.c_str());
    }
    catch(exception &err)
    {

    }
}
};

class TCPServer
{
public:
    // 初始化 服务器地址
    // const char* ip 如 127.0.0.1
    // int port       如 9888
    void init(const char* ip, int port);
    // 等待客户端连接(阻塞)
    void wait_listen();
    // 发送一条信息
    bool send_msg(const char* str);
    // 断开连接 并通知客户端也断开
    void unconnect(bool force=false);
    // 获取连接状态
    bool is_connect();
private:
    // 等待连接的 套接字
    int _sockfd;
    // 已经建立连接的套接字
    int _newsockfd;
    // 服务器地址
    struct sockaddr_in _serv_addr;
    // 客户端地址
    struct sockaddr_in _cli_addr;
    // 缓冲区
    char _buffer[TCP_BUFFER_SIZE];
    // 连接状态
    bool _connect{false};
};

void TCPServer::init(const char* ip, int port)
{
    uint32_t server_ip= inet_addr(ip);
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) 
        throw TCPError("ERROR opening socket");
    bzero((char *) &_serv_addr, sizeof(_serv_addr));

    _serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_addr.s_addr = server_ip;
    _serv_addr.sin_port = htons(port);
    
    int on = 1;
    int ret = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

    ret = bind(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr));
    printf("bind return %d socket:%d %s:%d\n", ret, _sockfd, inet_ntoa(_serv_addr.sin_addr), ntohs(_serv_addr.sin_port));
    if (ret < 0) 
        throw TCPError("ERROR on binding");
    else
        printf("server address %s:%d \r\n", inet_ntoa(_serv_addr.sin_addr), ntohs(_serv_addr.sin_port));
}

void TCPServer::wait_listen()
{
    listen(_sockfd,5);
    socklen_t clilen = sizeof(_cli_addr);
    _newsockfd = accept(_sockfd, (struct sockaddr *) &_cli_addr, &clilen);
    if (_newsockfd < 0) 
        throw TCPError("ERROR on accept");
    // 发生确认信息
    int n = write(_newsockfd,"hello I'm Server", 18);
    if (n < 0) 
        throw TCPError("ERROR writing to socket");
    // 接受确认信息
    bzero(_buffer, TCP_BUFFER_SIZE);
    n = read(_newsockfd,_buffer, TCP_BUFFER_SIZE);
    if (n < 0) 
        throw TCPError("ERROR reading from socket");
    printf("server address %s:%d accept client connect %s\n", inet_ntoa(_serv_addr.sin_addr), ntohs(_serv_addr.sin_port), _buffer);
    _connect = true;
}

bool TCPServer::send_msg(const char* str)
{
    if (!_connect)
        return false;
    int n = write(_newsockfd, str, strlen(str));
    if (n < 0) 
    {   char s[1024];
        sprintf(s, "ERROR in send:%s", str);
        throw TCPError(s);
    }
    return true;
}

void TCPServer::unconnect(bool force)
{   
    if (!force)
    {
        // 发生确认信息
        int n = write(_newsockfd,"unconnect", 18);
        if (n < 0) 
            throw TCPError("ERROR in unconnect");
    }
    if (!_connect)
    {
        close(_newsockfd);
        close(_sockfd);
        _connect = false;
    }
}


bool TCPServer::is_connect()
{
    return _connect;
}

int main(int argn, const char** argv)
{
    if (argn != 3)
    {
        printf("argn = %d != 3\n", argn);
        return -1;
    }
    if (atoi(argv[2]) == 0 )
    {
        printf("arg[2] %s is not numeric\n", argv[2]);
        return -1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    printf("address:%s:%s\n", argv[1], argv[2]);

    TCPServer server;
    server.init(ip, port);
    server.wait_listen();

    int count = 0;
    while (count < 200)
    {   
        char s[256];
        sprintf(s, "message%05d", ++count);
        try
        {
            if (server.send_msg(s))
                printf("server send %s\n", s);
        }
        catch (TCPError &err)
        {
            printf("error in tcp connect:%s\n", err.what());
            server.unconnect(true);
            usleep(10*1000);
            server.wait_listen();
            printf("reconnect");
            --count;
        }
        catch (...)
        {   
            printf("shjdaiojdhoaijdoaij\n");
            perror("error in tcp connect:...\n");
        }
        usleep(100*1000);
    }
    server.unconnect();
    printf("server exit\n");
    return 0;
}