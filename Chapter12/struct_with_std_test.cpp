#include <iostream>
using std::cout; using std::endl;
#include <cstring>
#include <vector>
using std::vector;

struct VEC_INT
{                                   // total size 56
    vector<int> arr;                // size 24 数组起始地址 数据结束地址 分配空间结束地址
    int tail[8];                    // size 32
};

// pBuff 需要打印的内存地址
// unsigned int nLen 需要打印的内存长度
// unsigned int nRowByte 每行显示的字节数 不要超过128 推荐8和16
// 打印内存
void PrintBuffer(void* pBuff, unsigned int nLen, unsigned int nRowByte)
{   // 打印内存
    if (NULL == pBuff || 0 == nLen)
    {
        return;
    }

    const int nBytePerLine = nRowByte;
    unsigned char* p = (unsigned char*)pBuff;
    char szHex[512] = {0};

    for (unsigned int i=0; i<nLen; ++i)
    {
        int idx = 3 * (i % nBytePerLine);
        if (0 == idx)
        {
            memset(szHex, 0, sizeof(szHex));
        }
        snprintf(&szHex[idx], 4, "%02x ", p[i]); // buff长度要多传入1个字节
        // 以16个字节为一行，进行打印
        if (0 == ((i+1) % nBytePerLine))
        {
            printf("%s\n", szHex);
        }
    }

    // 打印最后一行未满16个字节的内容
    if (0 != (nLen % nBytePerLine))
    {
        printf("%s\n", szHex);
    }

}

int main()
{
    VEC_INT* pvec_int = new VEC_INT;
    memset(pvec_int, 0, sizeof(VEC_INT));
    cout << "struct vec_int size: " << sizeof(VEC_INT) << endl;
    cout << "strut int      size: " << sizeof(int) << endl;
    PrintBuffer(&(pvec_int->arr), 32, 8);
    pvec_int->arr.push_back(1);
    PrintBuffer(&(pvec_int->arr), 32, 8);
    cout << pvec_int->tail[0] << endl;
    printf("struct             locate:%p\n", pvec_int);
    int * arr_st =  &(pvec_int->arr[0]);
    printf("size %lu vector[0] locate:%p\n", pvec_int->arr.size(), arr_st );
    for (int i=0; i<20; i++)
    {
        pvec_int->arr.push_back(1);
        if (arr_st != &(pvec_int->arr[0]))
        {   
            arr_st =  &(pvec_int->arr[0]);
            printf("size %lu vector[0] locate:%p\n", pvec_int->arr.size(), arr_st );
        }
    }
    PrintBuffer(&(pvec_int->arr), 32, 8);
    cout << pvec_int->tail[0] << endl;
    delete pvec_int;
}