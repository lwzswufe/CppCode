#include <stdio.h>

int main()
{
    char str1[32] = "0\t600004\t2329\t2.30000\t2.31000\n";
    char str2[32] = "0\t000004\t3327\t9.45000\t9.46999\n";
    char codes[8];
    int market, code, blank;
    float opens, highs;

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
    return 0;
}
