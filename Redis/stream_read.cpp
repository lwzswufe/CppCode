#include <hiredis/hiredis.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
/*
export LD_LIBRARY_PATH=/usr/local/lib
g++ -std=c++11  stream_read.cpp -o stream_read.out -I /usr/local/include/hiredis -lhiredis
*/


void ShowRedisReply(redisReply * reply, int deep=0, int idx=1)
{
    if (reply != nullptr)
    {
        if (reply->str != nullptr)
        {
            printf("deep:%d idx:%d reply:%p  str:%s\n", deep, idx, reply, reply->str);
        }
        else
        {
            printf("deep:%d idx:%d reply:%p  elements:%lu\n", deep, idx, reply, reply->elements);
            for (unsigned i=0; i<reply->elements; ++i)
            {
                
                redisReply * subReply = reply->element[i];
                ShowRedisReply(subReply, deep+1, i+1);
                // freeReplyObject(subReply);
            }
        }
    }
    else
    {
        printf("reply: nullptr\n");
    }
}

std::vector<std::vector<std::string>> ParseRedisReply(redisReply * reply)
{
    std::vector<std::vector<std::string>> vec{};
    if (reply == nullptr || reply->elements< 1)
        return vec;
    redisReply * subReply = reply->element[0];
    if (subReply == nullptr || subReply->elements< 2)
        return vec;
    subReply = subReply->element[1];
    if (subReply == nullptr || subReply->elements< 1)
        return vec;
    for (unsigned i=0; i<subReply->elements; ++i)
    {
        std::vector<std::string> subVec{};
        redisReply* subSubReply = subReply->element[i];
        if (subSubReply->elements < 2)
            continue;
        redisReply* IDReply = subSubReply->element[0];
        if (IDReply!= nullptr && IDReply->str != nullptr)
        {
            std::string ID = IDReply->str;
            subVec.push_back(ID);
        }
        else
        {
            continue;
        }
        redisReply* valueReply = subSubReply->element[1];
        if (valueReply == nullptr || valueReply->elements < 1)
        {
            vec.push_back(subVec);
            continue;
        }
        for (unsigned j=0; j<valueReply->elements; ++j)
        {
            redisReply* subValueReply = valueReply->element[j];
            if (subValueReply != nullptr && subValueReply->str != nullptr)
            {
                std::string value{subValueReply->str};
                subVec.push_back(value);
            }
        }
        vec.push_back(subVec);
    }
    return vec;
}

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

    /*XLEN*/
    char streamName[10]{"mystream"};
    reply = (redisReply *)redisCommand(client, "XLEN %s", streamName);
    int len{0};
    if (reply != nullptr)
    {
        printf("reply:%p  str:%p int:%d\n", reply, reply->str, reply->integer);
        len = reply->integer;
        freeReplyObject(reply);
    }
    else
    {
        printf("reply: nullptr\n");
    }
    if (len <= 0)
        return 0;
    /*XREAD*/
    reply = (redisReply *)redisCommand(client,"XREAD COUNT %d STREAMS %s 0-0", len, streamName);
    ShowRedisReply(reply);
    std::vector<std::vector<std::string>> valueVec = ParseRedisReply(reply);
    printf(">>>>>>>>>>>>>> show <<<<<<<<<<<<<<\n");
    for (std::vector<std::string> vec: valueVec)
    {
        for (std::string str: vec)
        {
            std::cout << str << ", ";
        }
        std::cout << std::endl;
    }
    freeReplyObject(reply);
    /*XDEL*/
    for (std::vector<std::string> vec: valueVec)
    {
        const std::string& ID = vec[0];
        reply = (redisReply *)redisCommand(client,"XDEL %s %s", streamName, ID.c_str());
        if (reply != nullptr)
        {
            printf("XDEL %s %s reply:%p  str:%p\n", streamName, ID.c_str(), reply, reply->str);
            freeReplyObject(reply);
        }
        else
        {
            printf("XDEL %s %s reply: nullptr\n", streamName, ID.c_str());
        }
    }
    return 0;
}