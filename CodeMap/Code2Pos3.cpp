#include <string.h>
#include "Code2Pos3.h"
namespace Code2Pos3
{
const int CODEARRSIZE{100 * 10000};
const int CODESIZE{7};

int* CODEARR{nullptr};
}
// 初始化查找表
void Code2Pos3::InitialSearchTable()
{   
    CODEARR = new int[CODEARRSIZE];
    memset(CODEARR, 0, sizeof(int) * CODEARRSIZE);
}

int Code2Pos3::FindCode(const char * code)
{   
    if (code == nullptr || strlen(code) < CODESIZE - 1)
        return 0;
    // 证券代码字符串转化为数组坐标 效率是map<string，int>的5倍
    int pos = (code[0] - '0')  * 100000 + (code[1] - '0') * 10000  +  (code[2] - '0') * 1000 +
              (code[3] - '0')  * 100 + (code[4] - '0') * 10  +  (code[5] - '0');
    return CODEARR[pos];
}

void Code2Pos3::ReleaseSearchTable()
{
    if (CODEARR != nullptr)
    {
        delete[] CODEARR;
        CODEARR = nullptr;
    }
}