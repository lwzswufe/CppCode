#include <cstdio>
#include <cstring>
// 字符串拆分
int main ()
{
    char str1[] ="- This, a sample string.";
    char * pch;
    const char Delimit[]{" ,.-"};

    printf("Splitting string \"%s\" into tokens:\n", str1);

    pch = strtok(str1, Delimit);
    while (pch != NULL)
    {
        printf ("%s\n", pch);
        pch = strtok(NULL, Delimit);
    }

    printf (">>>>>>>>>%s>>>>>>>\n", "strtok end");

    char str2[] ="- This, a sample string.";
    char *token = NULL;                     // 找到的字符串
    char *next_token = NULL;                // 剩下的字符串

    token = strtok_s(str2, Delimit, &next_token);
    
    char str3[] = "09:33:18.7450\t300484\t13.430000\t13.550000\t1\t1\t14\t3";
    const char seq[]{"\t"};
    char *s;
    s = str3;
    token = NULL;
    next_token = NULL; 
    token = strtok_s(s, seq, &next_token);
    printf("token0:%s\n", token);
    s = next_token;
    token = strtok_s(s, seq, &next_token);
    while (token != NULL)
    {
        printf ("token:%s\n", token);
        token = strtok_s(NULL, seq, &next_token);
    }

    printf (">>>>>>>>>%s>>>>>>>\n", "strtok_s end");
    return 0;
}