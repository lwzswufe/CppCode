#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h> 
#include <stdexcept>
#include <time.h>
using std::runtime_error;
#define TCP_BUFFER_SIZE 1024

class TCPError :public runtime_error
{
public: TCPError(const std::string &s) : runtime_error(s) {}
};

class TCPClient
{
public:
    // 初始化 服务器地址
    // const char* ip 如 127.0.0.1
    // int port       如 9888
    void init(const char* ip, int port);
    // 连接服务器
    void connect_server();
    // 获取一条信息(阻塞)
    const char* get_msg();
    // 断开连接
    void unconnect();
    // 获取连接状态
    bool is_connect();
private:
    // 套接字
    int _sockfd;
    // 服务器信息 包括主机名、别名、地址类型、地址长度和地址列表
    struct hostent *_server;
    // 服务器地址
    struct sockaddr_in _serv_addr;
    // 客户端地址
    struct sockaddr_in _cli_addr;
    // 缓冲区
    char _buffer[TCP_BUFFER_SIZE];
    // 连接状态
    bool _connect{false};
};

void TCPClient::init(const char* ip, int port)
{
    _server = gethostbyname(ip);
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) 
        throw TCPError("ERROR opening socket");
    if (_server == NULL)
    {
        throw TCPError("ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    bcopy((char *)_server->h_addr_list[0], 
         (char *)&_serv_addr.sin_addr.s_addr,
         _server->h_length);
    _serv_addr.sin_port = htons(port);

    printf("server address %s:%d\n", _server->h_name, ntohs(_serv_addr.sin_port));
}

void TCPClient::connect_server()
{
    if (connect(_sockfd,(struct sockaddr *) &_serv_addr,sizeof(_serv_addr)) < 0) 
        throw TCPError("ERROR connecting");
    printf("connect successful\n");
    int n = read(_sockfd,_buffer,TCP_BUFFER_SIZE);                    // recv data
    if (n < 0) 
        throw TCPError("ERROR reading from socket");
    printf("%s\n",_buffer);
    sprintf(_buffer, "Hello I'm Client");
    n = write(_sockfd, _buffer, strlen(_buffer));        // send data
    if (n < 0) 
        throw TCPError("ERROR writing to socket");
    bzero(_buffer, TCP_BUFFER_SIZE);
    _connect = true;
}

const char* TCPClient::get_msg()
{   
    if (!_connect)
        return nullptr;
    bzero(_buffer, TCP_BUFFER_SIZE);
    int n = read(_sockfd,_buffer,TCP_BUFFER_SIZE);                    // recv data
    if (n < 0) 
        throw TCPError("ERROR reading from socket");
    printf("client get %s\n", _buffer);
    if (strcmp(_buffer, "unconnect") == 0)
    {
        unconnect();
    }
    return _buffer;
}

void TCPClient::unconnect()
{   
    if (!connect)
    {
        _connect = false;
        close(_sockfd);
    }
}

bool TCPClient::is_connect()
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
    printf("ip:%s port:%s\n", argv[1], argv[2]);
    TCPClient client;
    client.init(ip, port);
    client.connect_server();
    int count = 0;
    while (count < 20)
    {   
        const char* str = client.get_msg();
        if (str != nullptr)
            printf("client get %s\n", str);
        ++count;
        usleep(100);
    }
    client.unconnect();
    printf("client exit\n");
    return 0;
}