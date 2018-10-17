#include <stdio.h>
#include <string.h>

/*
逐行按照制表符拆分数据
*/
int main()
{                                           
    const char Delimit[2] = "\n";
    char str[1024] = "0\t600004\t2329\t2.30000\t2.31000\t2.26000\t2.30000\n"
                     "0\t000004\t3327\t9.45000\t9.46999\t9.45000\t9.46999\n"
                     "0\t300231\t1257\t5.05000\t5.06999\t5.01001\t5.03999\n";
    const char scanf_format[16] = "%d\t%d\t%*d\t%f\t%f";
    char *token = NULL;                     // 找到的字符串
    char *next_token = NULL;                // 剩下的字符串
    int market, code;
    float opens, highs;

    token = strtok_s(str, Delimit, &next_token);
    
    while (token != NULL)
    {   
        code = market = 0;                  // 重置
        opens = highs = 0.0;                
        sscanf_s(token, scanf_format, &market, &code, &opens, &highs);
        printf_s("market: %d\tcode: %06d\topen: %.2f\thigh :%.2f\n", market, code, opens, highs);
        token = strtok_s(NULL, Delimit, &next_token);
    }

    printf (">>>>>>>>>%s>>>>>>>\n", "strtok_s end");
    return 0;
}