#include <iostream>
using std::cout; using std::endl;
#include <cstring>
#include <string.h>
using std::string;

#include <memory>
using std::unique_ptr;

#include <vector>
using std::vector;

unique_ptr<char [] > get_str(int i)
{
    unique_ptr<char [] > uni_s {new char [16]};
    char * s = uni_s.get();  
    sprintf(s, "num:%d", i);
    return uni_s;
}

int main()
{
    const char str1[13]{"12345678\n"};
    const char str2[13]{"abc\n"};
    char * str4 = new char[strlen(str1) + 1];               // new 数组的时候需要为\0额外分配一个空间
    strncpy(str4, str1, strlen(str1) + 1);
    string str3 = str1;
    cout << " char " << strlen(str1) << " string " << str3.size() << endl;
    printf("%p : %s\n", str4, str4 );
    delete [] str4;                                         // 释放内存
    printf("%p : %s\n", str4, str4 );

    unique_ptr<char [] > str5 {new char [13]};
    char * str6 = str5.get();                               // 获取管理的指针
    strncpy(str6, str1, strlen(str1) + 1);                  // str5.get()
    printf("%p : %s\n", &(str5[0]), &(str5[0]));

    vector<unique_ptr<char [] >> vec_u;
    vector<char *> vec_c;

    for ( int i=0; i<4; i++ )
    {
        vec_u.push_back(get_str(i));
        vec_c.push_back(vec_u[i].get());
    }
    printf("子函数返回 unique_ptr 后 其管理的内存继续存在\n");
    for ( int i=0; i<4; i++ )
        cout << vec_c[i] << endl;

    vec_u.clear();
    printf("unique_ptr 指针删除后 其所引用的内存自动释放\n");
    for ( int i=0; i<4; i++ )
        cout << vec_c[i] << endl;

    return 0;
}