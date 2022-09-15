#include <stdlib.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// 回调函数对象类型，当接收到消息后调用回调把消息发送出去
typedef void (*NotifyMessageFn)(const char *, const char *, int) ;    

class CRedisSubscriber
{
public:
    
    // 构造    
    CRedisSubscriber();
    // 析构
    ~CRedisSubscriber();
    // 初始化 传入回调对象
    bool Init(const NotifyMessageFn &fn);    
    // 
    bool Uninit();
    // 连接服务器
    bool Connect();
    // 断开连接
    bool Disconnect();
    // 订阅指定频道
    // 可以多次调用，订阅多个频道
    bool Subscribe(const std::string &channel_name);
    
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
    // 通知外层的回调函数对象
    NotifyMessageFn _notify_message_fn;
};