#include <iostream>
using std::cout; using std::endl;
#include <cstring>
typedef char CodeType[7];
struct Stock
{
    CodeType code;
    char market;
};
int main()
{
    CodeType code;
    strncpy_s(code, "600010", 7);
    cout << code << endl;
    Stock s{"600000", 0};
    printf("code:%s market:%d\n", s.code, s.market);
    char code_c[7] {"600014"};
    Stock s2{"", 0};
    strncpy_s(s2.code, code_c, 7);
    printf("code:%s market:%d\n", s2.code, s2.market);
}