#include <string.h>
#include "Code2Pos1.h"
namespace Code2Pos1
{
int CODEARRSIZE{40000};
int CODESIZE{7};

int* CODEARR{nullptr};
}
int Code2Pos1::FindCode(const char * code)
{    // 证券代码字符串转化为数组坐标 效率是map<string，int>的5倍
    if (code == NULL || strlen(code) < CODESIZE - 1)
        return 0;
    int base, pos;
    // char s[LOGSIZE];
    switch (code[0])
    {
    case '0':                                                     // 00X
        if(code[1] == '0')
            base = 0;
        else
            return 0;
		break;
	case '3':                                                     // 30X
		if(code[1] == '0')
            base = 10000;
        else
            return 0;
        break;
	case '6':
    {
        switch (code[1])
        {
        case '0': base = 20000;      break;                      // 60X;
        case '8': base = 30000;      break;                      // 68X;
		default:   
            return 0;                break;
        }                                                   
		break;
    }
	default:
        return 0;  // 返回0表示未找到
        // sprintf(s, "%s error code:%s out of range[0, %d]\n", __func__, code, CODEARRSIZE);
        // throw range_error(s);
        // printf(s);
    }
    pos = base + (code[2] - 48) * 1000 
               + (code[3] - 48) * 100
			   + (code[4] - 48) * 10
			   + (code[5] - 48);
    if (pos < 0 || pos > CODEARRSIZE)
        return 0;
    else
        return CODEARR[pos];
}

void Code2Pos1::InitialSearchTable()
{   
    CODEARR = new int[CODEARRSIZE];
    memset(CODEARR, 0, sizeof(int) * CODEARRSIZE);
}

void Code2Pos1::ReleaseSearchTable()
{
    if (CODEARR != nullptr)
    {
        delete[] CODEARR;
        CODEARR = nullptr;
    }
}