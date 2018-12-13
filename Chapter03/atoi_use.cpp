#include <cstdio>
#include <cstring>
#include <cstdlib>     /* atoi */
int main()
{
    char str1[5]="1234", str2[5]="ABCD", str3[5]="A123", str4[5]="123A", str5[5]="12.3";
    int a;
    a = atoi(str1);
    printf("%s:%d\n", str1, a);
    a = atoi(str2);
    printf("%s:%d\n", str2, a);
    a = atoi(str3);
    printf("%s:%d\n", str3, a);
    a = atoi(str4);
    printf("%s:%d\n", str4, a);
    a = atoi(str5);
    printf("%s:%d\n", str5, a);
}