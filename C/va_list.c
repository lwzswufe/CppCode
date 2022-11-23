#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "stdarg.h"


/*
可变参数 函数
gcc va_list.c -o va_list.out
*/



int sum(const char* msg, ...);


void print(const char* head, ...)
{       
    printf("%s", head);
    // 解析可变参数
    va_list args;
    va_start(args, head);
    while (1)
    {
        const char* key = va_arg(args, const char*);
        int value = va_arg(args, int);
        if (isalpha(key[0]))
        {
            printf(",\"%s\":%d", key, value);
        }
        else
        {
            break;
        }
        
    }
    printf("\n");
    va_end(args);
}

int main()
{
    int total = 0;
    total = sum("hello world", 1, 2, 3);
    printf("total = %d\n", total);
    print("hello", "age", 38, "weight", 78);
    return 0;
}

int sum(const char* msg, ...)
{
    va_list vaList; //定义一个具有va_list型的变量，这个变量是指向参数的指针。
    va_start(vaList, msg);//第一个参数指向可变列表的地址,地址自动增加，第二个参数位固定值
    printf("param msg:%s\n", msg);
    int sumNum = 0;
    int step = 0;
    int i = 0;
    while ( 0 != (step = va_arg(vaList, int)))//va_arg第一个参数是可变参数的地址，第二个参数是传入参数的类型，返回值就是va_list中接着的地址值，类型和va_arg的第二个参数一样
    {                          //va_arg 取得下一个指针 它无法判断检索到的参数是否是传给函数的最后一个参数
        ++i;
        printf("get arg%d: %d\n", i, step);
        //不等于0表示，va_list中还有参数可取
        sumNum += step;
    }
    va_end(vaList);//结束可变参数列表
    return sumNum;
}