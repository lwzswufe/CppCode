#include <stdio.h>
#include <string.h>

/*
多次使用sscanf 并且期间会移动指针
*/


int main()
{
    char exm[256] = "20170103\t20170103093939000\t20170103093939166\t20170103093842064\t20170103093842065\t1013\t000725\t102 \tNN010\t2.930000";
    char* line = exm;
    int match_num, date, ChannelNo, MarketNo;
    match_num = sscanf(line, "%d", &date);
    // 执行完sscanf 后 line保持位置不变 指向字符串第一个位置
    printf("%s\n", line);
    line += 81;
    // 通过%*nc来跳过n个字符
    match_num = sscanf(line, "%d%*d%*d \t%*2c%d", &ChannelNo, &MarketNo);
    char code[8];
    line += 5;
    strncpy(code, line, 6);
    code[6] = 0;
    printf("date:%d, channel:%d Market:%d code:%s", date, ChannelNo, MarketNo, code);
    return 0;
}