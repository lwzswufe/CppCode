#include <cstdio>
#include <cstring>
typedef char *Str;
// 复制字符数组
int main()
{
    
    char str1[]="Sample string";
    char str2[40];
    char str3[40];
    char str4[40];
    Str str5 = new char[40];
    const char strc[20] = "const char []";
    const char *str_p = &strc[0];
    strcpy (str2,str1);
    strcpy (str3,"copy successful");
    printf ("str1: %s\nstr2: %s\nstr3: %s\n\n",str1,str2,str3);

    strcpy_s(str2,str1);
    strcpy_s(str3,"copy successful");
    printf_s("str1: %s\nstr2: %s\nstr3: %s\n\n",str1,str2,str3);

    strcpy_s(str4,str_p);
    printf_s("strp: %s\nstr4: %s\n\n", str_p, str4);
    
    strcpy_s(str5, 40, str_p);        // 不可直接使用    strcpy_s(str5, str_p) 40用于指明str5的大小
    printf_s("strp: %s\nstr4: %s\n\n", str_p, str5);
    return 0;
}