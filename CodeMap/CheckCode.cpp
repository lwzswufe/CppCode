#include <iostream>
using std::cout;
using std::endl;
using std::hex;
using std::oct;

// 检查字符长度为6 且字符仅包含0~9 :;<>=?
bool inline CheckCodeLength(const char * code)
{
    int a = (code[0] & code[1] & code[2] & code[3] & code[4] & code[5]) >> 4;
    int b = (code[0] | code[1] | code[2] | code[3] | code[4] | code[5]) >> 4;
    return a == 3 && b == 3 && code[6] == 0;
}


int main()
{
    char code[8][12] {"623594", "0", "", "dq4dq4", "\00056231", "6536987", "1549:;", "51qtx5"};
    for (int i=0; i<8; ++i)
    {   

        cout << CheckCodeLength(code[i]) << ":" << code[i] << endl; 
    }
    return 0;
}