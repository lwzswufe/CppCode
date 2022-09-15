/*************************************************************************
    > File Name: redis_publisher.h
    > Author: chenzengba
    > Mail: chenzengba@gmail.com 
    > Created Time: Sat 23 Apr 2016 10:15:09 PM CST
    > Description: 封装hiredis，实现消息发布给redis功能
 ************************************************************************/
 
#ifndef REDIS_PUBLISHER_H
#define REDIS_PUBLISHER_H
 
#include <stdlib.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
 
class CRedisPublisher
{
public:   
    // 构造
    CRedisPublisher();
    // 析构
    ~CRedisPublisher();
    // 初始化
    bool Init();
    bool Uninit();
    // 连接服务器
    bool Connect();
    // 断开连接
    bool Disconnect();
    // 发布信息
    bool Publish(const std::string &channel_name, 
        const std::string &message);
 
private:
     // 下面三个回调函数供redis服务调用
    // 连接回调
    static void ConnectCallback(const redisAsyncContext *redis_context,
        int status);
	
	// 断开连接的回调
    static void DisconnectCallback(const redisAsyncContext *redis_context,
        int status);
 
	// 执行命令回调
    static void CommandCallback(redisAsyncContext *redis_context,
        void *reply, void *privdata);
 
    // 事件分发线程函数
    static void *EventThread(void *data);
    // 事件
    void *EventProc();
 
private:
     // libevent事件对象
    event_base *_event_base;
	// 事件线程ID
    pthread_t _event_thread;
	// 事件线程的信号量
    sem_t _event_sem;
	// hiredis异步对象
    redisAsyncContext *_redis_context;
};
 
#endif