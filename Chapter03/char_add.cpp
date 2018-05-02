/*
extern char *strcat(char *dest, const char *src);
头文件
在C中，函数原型存在 <string.h>头文件中。
在C++中，则存在于<cstring>头文件中。
功能
把src所指字符串添加到dest结尾处(覆盖dest结尾处的'\0')。
说明
src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。
返回指向dest的指针。
*/
#include <stdio.h>

#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include <cstring>

int main()
{   
    char *s_ptr, *s_ptr2;

    char s1[] = "sdaidia";

    //string str_0 = "sdada";

    //s_ptr2 = &str_0[0];

    //cout << s_ptr2 << endl;

    //char *s2 = &s1; 

    double a = 1543.151168;

    sprintf(s_ptr, "a=%.4f", a);
    sprintf(s_ptr2, "a=%.3f", a);

    cout << s_ptr << " == " << s1 << "    ";
    cout << (strcmp(s_ptr, s1) ? "True" : "False") << endl;

    strcat(s_ptr, s1);         // s += str0

    //strcat(s_ptr2, s_ptr);         // s += str0

    //strcat(s_ptr2, s1);         // s += str0

    //cout << s_ptr2 << endl;

    cout << s_ptr << "\t小数点后4位" << endl;

    cout << strlen(s_ptr) << endl;

    cout << strlen(s1) << endl;
    //cout << "length: " << strlen(s1) << endl;
    //strcat(s2, s1);  

    //cout << s2 << endl;

    return 0;
}