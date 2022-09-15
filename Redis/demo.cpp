#include <hiredis/hiredis.h>
#include <string.h>
#include <stdlib.h>
/*
export LD_LIBRARY_PATH=/usr/local/lib
g++ -std=c++11  demo.cpp -o demo.out -I /usr/local/include/hiredis -lhiredis
*/
int main(int argn, char** argv)
{
    const char *ip{nullptr};
    int port{0};
    if (argn < 3)
    {   
        printf("please input ip and port\n");
        return -1;
    }
    else
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }
    // 该函数用于创建redis的链接。redisContext保存链接的状态
    // 在redisContext结构体中包含了一个整形变量err，当err不为0时，errstr变量中保存错误描述。在链接之后需要对链接状态进行检查。如下代码为官方提供：
    redisContext *client = redisConnect(ip, port);
    redisReply *reply{nullptr};
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    // redisContext *client = redisConnectWithTimeout(ip, port, timeout);
    // redisContext *client = redisConnectWithTimeout(ip, port, timeout);
    if (client == nullptr)
    {
        printf("get nullptr in login redis server %s:%d\n", ip, port);
        return -1;
    }
    else if(client->err != 0)
    {
        printf("error:%s in login redis server %s:%d\n", client->errstr, ip, port);
        return -1;
    }
    printf("successful in login redis server %s:%d\n", ip, port);

    /* Set */
    reply = (redisReply *)redisCommand(client,"SET %s %s", "welcome", "Hello, DCS for Redis!");
    if (reply == nullptr)
        printf("error in Set Data\n");
    else
    {
        printf("SET: %s\n", reply->str);
        freeReplyObject(reply);
    }

    /* Get */
    reply = (redisReply *)redisCommand(client,"GET welcome");
    if (reply == nullptr)
        printf("error in Set Data\n");
    else
    {
        printf("GET welcome: %s\n", reply->str);
        freeReplyObject(reply);
    }

    redisFree(client);
    return 0;
}
