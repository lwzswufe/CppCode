#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

void print_char_arr(char* s, int n)
{
    for(int i=0; i<n; i++)
        if (s[i] != 0)
            printf("%c", s[i]);
        else
            printf(" ");
    printf("___char_arr_end\n");
}
int main()
{
    string code{"611523"}, code2{"sdawqwq"};
    char code_[7]{"611523"};
    char ss[256], *st;
    st = ss;
    strcpy_s(ss, code.size()+1, code.c_str());  // 复制区间长度需为string.size() + 1 否则会发生复制不完全的情况
    print_char_arr(st, 64);
    //ss += code.size();                          // ss偏移量为string.size() 重置掉字符串末尾的\0结束符               
    strcpy_s(ss + code.size(), code2.size()+1, code2.c_str());
    print_char_arr(st, 64);
    return 0;
}
