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

    /* Get no Data */
    reply = (redisReply *)redisCommand(client,"GET welcome2");
    if (reply == nullptr)
        printf("error in Set Data\n");
    else
    {   
        // 没有数据时 reply->str为空指针
        printf("GET welcome2 (no data): %s\n", reply->str);
        freeReplyObject(reply);
    }

    /* RPUSH */
    char listName[32] {"list"};
    for (int i=0; i<5; ++i)
    {
        char value[32];
        sprintf(value, "user%03d", i+101);
        reply = (redisReply *)redisCommand(client,"RPUSH %s %s", listName, value);
        printf("RPUSH %s %s\n", listName, value);
        freeReplyObject(reply);
    }
    /* LRANGE */
    reply = (redisReply *)redisCommand(client,"LLEN %s", listName);
    if (reply != nullptr)
    {
        printf("len:%lld\n", reply->integer);
        int len = reply->integer;
        int start{0}, end{len};
        redisReply * replyRange =  (redisReply *)redisCommand(client,"LRANGE %s %d %d", listName, start, end);
        if (replyRange != nullptr)
        {
            size_t size = replyRange->elements;
            redisReply ** replyArr = replyRange->element;
            printf("size:%lu arr:%p\n", size, replyArr);
            for (unsigned i=0; i<size; ++i)
            {
                printf("Arr[%u] = %s\n", i, replyArr[i]->str);
            }
            freeReplyObject(replyRange);
        }
    }
    freeReplyObject(reply);
    /* LPOP */
    reply = (redisReply *)redisCommand(client,"LPOP %s", listName);
    while(reply != nullptr && reply->str != nullptr)
    {
        printf("LPOP %s %s\n", listName, reply->str);
        freeReplyObject(reply);
        reply = (redisReply *)redisCommand(client,"LPOP %s", listName);
    }
    if (reply != nullptr)
    {
        printf("reply:%p  str:%p\n", reply, reply->str);
        freeReplyObject(reply);
    }
    else
    {
        printf("reply: nullptr\n");
    }
    /* HSET */
    char hashName[32] {"hmap"};
    for (int i = 0; i < 5; i++)
    {
        char fieldName[32], value[32];
        sprintf(fieldName, "%06d", i+1);
        sprintf(value, "data%d", i+1);
        reply = (redisReply *)redisCommand(client,"HSET %s %s %s", hashName, fieldName, value);
        if (reply != nullptr)
        {
            printf("HSET %s[%s] = %s\n", hashName, fieldName, value);
            freeReplyObject(reply);
        }
    }
    
    /* GSET */
    for (int i = 0; i < 5; i++)
    {
        char fieldName[32];
        sprintf(fieldName, "%06d", i+1);
        reply = (redisReply *)redisCommand(client,"HGET %s %s", hashName, fieldName);
        if (reply != nullptr)
        {
            printf("HGET %s[%s] = %s\n", hashName, fieldName, reply->str);
            freeReplyObject(reply);
            
        }
    }
    redisFree(client);
    return 0;
}
