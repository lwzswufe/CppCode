#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include <chrono>

/*
g++ sem_linux.cpp -lpthread -std=c++11 -o sem_linux.o
*/

sem_t SEM;
int N{3}, SLEEP_US{10};

// 等待信号量执行的函数
void *func1(void *arg)
{
    for (int i=0; i<N; i++)
    {
        // 阻塞 等待信号量
        sem_wait(&SEM);
        int *running = (int *)arg;
        printf("thread pop running : %d\n", *running);
    }    
    // 线程退出
    pthread_exit(NULL);
}

// 发送信号量的函数
void *func2(void *arg)
{
    for (int i=0; i<N; i++)
    {   
        int *running = (int *)arg;
        printf("thread push running :%d\n", *running);
        (*running)++;
        // 发送信号量
        sem_post(&SEM);
        usleep(SLEEP_US);
    }
    // 线程退出
    pthread_exit(NULL);
}
    
int main(int argn, char** argc)
{   
    if (argn >= 2)
        N = atoi(argc[1]);
    if (argn >= 3)
        SLEEP_US = atoi(argc[2]);
    int a = 0;
    printf("N = %d SLEEP_US = %d\n", N, SLEEP_US);
    // 信号量初始化
    sem_init(&SEM, 0, 0);
    // 定义线程数组
    pthread_t thread_id[2];
    // 创建执行信号量线程
    pthread_create(&thread_id[0], NULL, func1, (void *)&a);
    printf("main thread pop running.\n");
    // 创建发信号量线程
    pthread_create(&thread_id[1], NULL, func2, (void *)&a);
    printf("main thread push running.\n");
    // 等待线程结束
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);
    // 回收信号量
    sem_destroy(&SEM);
    return 0;
}