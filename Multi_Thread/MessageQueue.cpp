#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include <unistd.h>


/*
g++ -std=c++11 MessageQueue.cpp -o MessageQueue.out

得到消息队列标识符或创建一个消息队列对象并返回消息队列标识符
key       0(IPC_PRIVATE)：会建立新的消息队列 
          大于0的32位整数：视参数msgflg来确定操作。通常要求此值来源于ftok返回的IPC键值
msgflg    0：取消息队列标识符，若不存在则函数会报错
          IPC_CREAT：当msgflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列，返回此消息队列的标识符
          IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错


int msgget(key_t key, int msgflg)
成功：返回消息队列的标识符
出错：-1，错误原因存于error中
EACCES：指定的消息队列已存在，但调用进程没有权限访问它
EEXIST：key指定的消息队列已存在，而msgflg中同时指定IPC_CREAT和IPC_EXCL标志
ENOENT：key指定的消息队列不存在同时msgflg中没有指定IPC_CREAT标志
ENOMEM：需要建立消息队列，但内存不足
ENOSPC：需要建立消息队列，但已达到系统的限制
*/


#define MSGKEY 123                  // 消息队列编号
#define MESSAGE_SIZE 2040           // 消息部分长度
#define MESSAGE_TYPE_STRING 1       // 定义消息类型
//消息的数据结构是以一个长整型成员变量开始的结构体
struct Message
{
	long msgtype;                       // 消息类型
	char msgtext[MESSAGE_SIZE];         // 消息内容
};


void TaskProducer(int msqid)
{   

    printf("process producer start\n");
    char line[1024], filename[256]{"MessageQueue.txt"};
    FILE* f = fopen(filename, "r");
    if (f == nullptr)
    {   
        printf("file %s not exit\n", filename);
        exit(1);
    }
    else
    {
        printf("open file %s successful\n", filename);
    }
    //父进程
    while (fgets(line, 1024, f) != NULL)
    {   
        int n{0}, len{0};
        // 待发送信息
        Message msgs;
        msgs.msgtype = MESSAGE_TYPE_STRING;
        sscanf(line, "%d %s\n", &n, msgs.msgtext);
        usleep(n);
        // strncpy(msgs.msgtext, line+len, MESSAGE_SIZE);
        msgs.msgtext[MESSAGE_SIZE - 1] = 0;
        //发送消息队列(sizeof消息的长度，而不是整个结构体的长度)
        int ret = msgsnd(msqid, &msgs, sizeof(msgs.msgtext), IPC_NOWAIT);
        if (ret < 0)
        {
            printf("msgsnd() write msg failed,errno=%d[%s]\n", errno, strerror(errno));
            fclose(f);
            exit(-1);
        }
    }
    fclose(f);
    printf("process producer end\n");
}

void TaskConsumer(int msqid)
{   
    printf("process consumer start\n");
    const char exitstr[8]{"exit"};
    // 子进程
    while (true)
    {
        // 待接收信息
        Message msgs;
        msgs.msgtype = MESSAGE_TYPE_STRING;
        // 接收消息队列(sizeof消息的长度，而不是整个结构体的长度)
        int ret = msgrcv(msqid, &msgs, sizeof(msgs.msgtext), msgs.msgtype, IPC_NOWAIT);
        if (ret > 0)
        {
            printf("read msg:%s\n", msgs.msgtext);
            // 终止进程
            if (strcmp(exitstr, msgs.msgtext) == 0)
            {
                break;
            }
        }
    }
    printf("process consumer end\n");
}


int main()
{   
    //检查消息队列是否存在
	int msqid = msgget(MSGKEY, IPC_EXCL);//(键名,权限)
	if (msqid < 0)
	{
		//创建消息队列
		msqid = msgget(MSGKEY, IPC_CREAT | 0666);
		if (msqid <0)
		{
			printf("failed to create msq | errno=%d [%s]\n", errno, strerror(errno));
			exit(-1);
		}
        else 
            printf("create message queue:%d\n", msqid);
	}
    else
        printf("message queue:%d exists\n", msqid);
    int pid = fork();
    if (pid > 0)
        TaskProducer(msqid);
    else if (pid == 0)
        TaskConsumer(msqid);
    else
    {
        // 删除消息队列
        printf("delete message queue:%d\n", msqid);
        msgctl(msqid, IPC_RMID, 0);
        exit(1);
    }
    // 删除消息队列
    printf("delete message queue:%d\n", msqid);
	msgctl(msqid, IPC_RMID, 0);
	exit(1);
    return 0;
}