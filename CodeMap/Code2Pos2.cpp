#include <string.h>
#include "Code2Pos2.h"
namespace Code2Pos2
{

const int CODEARRSIZE{13 * 4096};
const int CODESIZE{7};

int* HEADARR{nullptr};    // 000-999
int* CODEARR{nullptr};
}
// 初始化查找表
void Code2Pos2::InitialSearchTable()
{   
    HEADARR = new int[4096];
    memset(HEADARR, 0, sizeof(HEADARR));
    HEADARR[0] = 1;    // 000
    HEADARR[1] = 2;    // 001
    HEADARR[2] = 3;    // 002
    HEADARR[3] = 4;    // 003
    HEADARR[3 * 256] = 5;    // 300
    HEADARR[3 * 256 + 1] = 6;    // 301
    CODEARR = new int[CODEARRSIZE];
    memset(CODEARR, 0, sizeof(CODEARRSIZE));
}

int Code2Pos2::FindCode(const char * code)
{   
    if (code == NULL || strlen(code) < CODESIZE - 1)
        return 0;
    int head = ((code[0] - '0') << 8) + ((code[1] - '0') << 4)  +  (code[2] - '0');
    int tail = ((code[3] - '0') << 8) + ((code[4] - '0') << 4)  +  (code[5] - '0');
    int pos = (HEADARR[head] << 12) + tail;
    // 证券代码字符串转化为数组坐标 效率是map<string，int>的10倍
    // int head = (code[0] - '0')  * 100 + (code[1] - '0') * 10  +  (code[2] - '0');
    // int tail = (code[3] - '0')  * 100 + (code[4] - '0') * 10  +  (code[5] - '0');
    // int pos = HEADARR[head] * 1000 + tail;
    return CODEARR[pos];
}


// 检查字符长度为6 且字符仅包含0~9 :;<>=?
bool inline CheckCodeLength(const char * code)
{
    int a = (code[0] & code[1] & code[2] & code[3] & code[4] & code[5]) >> 4;
    int b = (code[0] | code[1] | code[2] | code[3] | code[4] | code[5]) >> 4;
    return a == 3 && b == 3 && code[6] == 0;
}

int Code2Pos2::FindCode2(const char * code)
{   
    if (code == nullptr || !CheckCodeLength(code));
        return 0;
    int head = ((code[0] - '0') << 8) + ((code[1] - '0') << 4)  +  (code[2] - '0');
    int tail = ((code[3] - '0') << 8) + ((code[4] - '0') << 4)  +  (code[5] - '0');
    int pos = (HEADARR[head] << 12) + tail;
    // 证券代码字符串转化为数组坐标 效率是map<string，int>的10倍
    // int head = (code[0] - '0')  * 100 + (code[1] - '0') * 10  +  (code[2] - '0');
    // int tail = (code[3] - '0')  * 100 + (code[4] - '0') * 10  +  (code[5] - '0');
    // int pos = HEADARR[head] * 1000 + tail;
    return CODEARR[pos];
}

void Code2Pos2::ReleaseSearchTable()
{   
    if (CODEARR != nullptr)
    {
        delete[] CODEARR;
        CODEARR = nullptr;
    }
    if (HEADARR != nullptr)
    {
        delete[] HEADARR;
        HEADARR = nullptr;
    }
}
