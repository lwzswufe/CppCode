#include<iostream>
using std::cout; using std::endl;

#include<cstdio>

#include<cstring>

int main()
{   
    double a1=0.01646468, a2=30.5146;
    char str_1[20], str_2[20], str_3[20];               // 一定要声明大小 不然可能会引发内存错误

    sprintf(str_1, "aa = %.2f", a1);
    sprintf(str_2, "aa = %.4f", a2);

    cout << str_1 << " len: " << strlen(str_1) << endl; // cstring
    cout << str_2 << " len: " << strlen(str_1) << endl;

    strcpy(str_3, str_1);
    cout << str_3 << endl;

    strcat(str_3, str_2);
    cout << str_3 << endl;

    return 0;
}