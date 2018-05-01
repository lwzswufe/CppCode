#include <stdio.h>

#include <string>
using std::string;

#include <iostream>
using std::cout; using std::endl; using std::ostream;


int main()
{   
    char *s;
    double a=15264.21648431;
    int aa=1543;

    char c = 'a';
    //string str0="sda";
    // cout << str + c << endl;

    sprintf(s, "a=%.4f", a);
    //cout << *(s+2) << endl;
    cout << s << "\t小数点后4位" << endl;

    sprintf(s, "a=%06d", aa);
    cout << s << "\t输出6位十进制整数" << endl;

    sprintf(s, "a=%6d", aa);
    cout << s << "\t输出6位十进制整数" << endl;

    sprintf(s, "a=%6d", aa);
    cout << s << "\t左对齐6位十进制整数" << endl;

    sprintf(s, "a=%p", &a);
    cout << s << "\t地址" << endl;

    return 0;
}

