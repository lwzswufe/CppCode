#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define BOOLARRSIZE 16

// 读取char[] 根据其中的'0' '1' 生成一个 int16 即short类型数字
int bitchar2int(char strarr[])
{
    int size = strlen(strarr), x = 0, idx=0;
    for(int i=0; i<size; i++)
    {   
        if ( strarr[i] == '1')
        {   
            x = x << 1;
            ++x;
            ++idx;
        }
        else if (strarr[i] == '0')
        {   
            x = x << 1;
            ++idx;
        }
    }
    printf("01char_num:%d\n", idx);
    for (; idx<BOOLARRSIZE; idx++)
    {
        x = x << 1;
    }
    return x;
}

// 传入一个数字x 将其转化为bool数组
void int2boolarr(int x, bool bool_arr[])
{   
    int bool_num = 0;
    printf("x: %d\n", x);
    for(int i=0; i<BOOLARRSIZE; i++)
    {   
        bool_arr[BOOLARRSIZE - i - 1] = x % 2;
        x /= 2;
    }
}


// 编译 gcc boolarr2int.c -o boolarr2int.o
// 运行 boolarr2int.o 0000_0001_1011
int main(int argn, char** args)
{   
    char *str;
    if (argn != 2)
    {
        printf("please input bit array like: '0101001' \n");
        return 0;
    }
    else
        str = args[1];
    printf("%s\n", str);
    int length = strlen(str);
    if (length == 0)
    {
        printf("error bit array length: %d  \n", length);
    }
    int x;
    bool bool_arr[BOOLARRSIZE];
    x = bitchar2int(str);
    printf("get int:%d :%x\n", x, x);
    int2boolarr(x, bool_arr);
    for (int i=0; i<BOOLARRSIZE; ++i)
    {
        printf("%d", bool_arr[i]);
        if (i % 4 == 3)
            printf(" ");
    }
    printf("\n");
    return 0;
}