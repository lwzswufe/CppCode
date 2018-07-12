#include <stdio.h>
#include <string.h>
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
    
    while (token != NULL)
    {
        printf ("%s\n", token);
        token = strtok_s(NULL, Delimit, &next_token);
    }

    printf (">>>>>>>>>%s>>>>>>>\n", "strtok_s end");
    return 0;
}