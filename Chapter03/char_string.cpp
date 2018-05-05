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

char 和 string1的互相转化

string::c_str()：生成一个const char*指针，指向以空字符终止的数组。 
*/

#include<cstdio>

#include<iostream>
using std::cout; using std::endl;

#include<string>
using std::string;

#include<cstring>

int main()
{    
    string str_1 = "dahdaho", str_2, str_3;

    char char_1[20], char_2[20];

    const char* char_ptr, char_ptr2;

    cout << "string to char[]" << endl;
    strcpy(char_1, str_1.c_str());

    cout << char_1 << endl;

    cout << "char[] to string" << endl;
    str_2 = char_1;

    str_2 += "_2";

    cout << str_2 << endl;

    cout << "string to const char*" << endl;
    char_ptr = str_2.data();

    cout << char_ptr << endl;

    cout << "const char* to char []" << endl;
    strcpy(char_2, char_ptr);

    cout << char_2 << endl;

    cout << "const char* to string" << endl;
    str_3 = char_ptr;
    cout << str_3 << endl;

    return 0;
}