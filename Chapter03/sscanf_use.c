#include <stdio.h>
#include <string.h>
int main()
{
    char str1[32] = "0\t600004\t2329\t2.30000\t2.31000\n";
    char str2[32] = "0\t000004\t3327\t9.45000\t9.46999\n";
    char str3[128] = "09:30:29\t603988\t中电电机\t0\t买入\t信用交易\t已撤\t18.8800\t9100.00\n";
    char codes[8], timestr[16], name[16], buyorsell[16], ordertype[16];
    int market, code, blank;
    float opens, highs, price, vol;

    sscanf_s(str1, "%d\t%d\t%d\t%f\t%f", &market, &code, &blank, &opens, &highs);
    printf_s("%d,%06d,%d,%.2f,%.2f\n", market, code, blank, opens, highs);

    opens=highs=0.0;

    printf("%%s %%c 会干扰识别\n");
    sscanf_s(str2, "%d\t%s\t%*d\t%f\t%f", &market, codes, &opens, &highs);
    printf_s("%d,%s,____,%.2f,%.2f\n", market, codes, opens, highs);

    opens=highs=0.0;
    printf("%%*d 表示忽略\n");
    sscanf_s(str2, "%d\t%d\t%*d\t%f\t%f", &market, &code, &opens, &highs);
    printf_s("%d,%06d,____,%.2f,%.2f\n", market, code, opens, highs);

    printf("对于字符串需要分批次识别\n");
    sscanf_s(str3, "%s\t", timestr);
    printf_s("%s\n", timestr);
    sscanf_s(str3 + strlen(timestr), "%s\t", codes);
    printf_s("%s\n", codes);
    return 0;
}
