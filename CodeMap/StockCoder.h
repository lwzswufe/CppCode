#include <string.h>

// 股票代码段结构体
struct CodeSegment
{
    char head[4];           // 代码段名称 如 "001" "301" "688"
    short count;            // 代码段中代码数量
    void* arr;              // 数据储存地址
    CodeSegment* next;      // 下一个节点
};

template <typename T>
class StockCoder
{
private:
    // 尾部代码数组大小 16*16*16
    static const int tailArrSize{4096};
    // 头部代码数组大小 16*16*16
    static const int headArrSize{4096};
    // 证券代码前三位映射字典
    T** _headArr[tailArrSize];
    // 证券代码段链表 头节点为默认数据
    CodeSegment _head;
    // 股票数组的数量
    int headNum{0};
    /* data */
public:
    // 构造
    StockCoder();
    // 析构
    ~StockCoder();
    // 添加证券代码
    bool AddCode(const char* code);
    // 查找证券代码对应的数据
    T* FindCode(const char* code);
    // 储存数据
    bool StroageCode(const char* code, T *data);
};

template <typename T>
StockCoder<T>::StockCoder()
{   
    //  defaultArr 储存头三位错误的证券代码 的数据指针 全是nullptr 是查询的默认结果
    T** defaultArr = new T*[tailArrSize];
    memset(defaultArr, 0, tailArrSize * sizeof(T*));
    // 重置headArr 使得所有头三位代码查询结果指向默认结果
    for (int i=0; i<headArrSize; ++i)
        _headArr[i] = defaultArr;
    // 记录数据地址
    _head.arr = defaultArr;
}

template <typename T>
StockCoder<T>::~StockCoder()
{   
    CodeSegment* curSeg = &_head, *nextSeg=_head.next;
    // 释放默认数组内存
    // if (curSeg->arr != nullptr)
    //     delete[] (T*[tailArrSize]) curSeg->arr;
    curSeg->arr = nullptr;
    curSeg->next = nullptr;
    // 释放各个代码段的内存
    while(nextSeg != nullptr)
    {   
        curSeg = nextSeg;
        nextSeg = curSeg->next;
        // 释放数组内存
        // if (curSeg->arr != nullptr)
        //     delete[] (T*[tailArrSize]) curSeg->arr;
        // 重置地址信息
        curSeg->arr = nullptr;
        curSeg->next = nullptr;
        // 释放链表内存
        delete curSeg;
    }
}

// 检查字符长度为6 且字符仅包含0~9 :;<>=?
bool inline CheckCodeLength(const char * code)
{
    int a = (code[0] & code[1] & code[2] & code[3] & code[4] & code[5]) >> 4;
    int b = (code[0] | code[1] | code[2] | code[3] | code[4] | code[5]) >> 4;
    return a == 3 && b == 3 && code[6] == 0;
}

// 添加证券代码
template <typename T>
bool StockCoder<T>::AddCode(const char* code)
{
    if (code == nullptr || !CheckCodeLength(code))
        return false;
    // 验证所有位置都是整数 0-9 剔除 :;<>=? 的情况
    bool isNum = isdigit(code[0]) && isdigit(code[1]) && isdigit(code[2]) && isdigit(code[3]) && isdigit(code[4]) && isdigit(code[5]);
    if (!isNum)
        return false;
    // 寻找对应的股票代码段
    CodeSegment* curSeg{&_head}, *nextSeg{_head.next};
    while(nextSeg != nullptr)
    {
        curSeg = nextSeg;
        // 检查证券代码前三位是否一致
        if (curSeg->head[0] == code[0] && curSeg->head[1] == code[1] && curSeg->head[2] == code[2])
        {
            curSeg->count++;
            return true;
        }
        nextSeg = curSeg->next;
    }
    // 创建新的代码段结构体
    curSeg->next = new CodeSegment;
    curSeg = curSeg->next;
    // 初始化代码段信息
    curSeg->next = nullptr;
    curSeg->count = 1;
    ++headNum;
    strncpy(curSeg->head, code, 3);
    curSeg->head[3] = 0;
    // 代码段寻址
    int head = ((code[0] - '0') << 8) + ((code[1] - '0') << 4)  +  (code[2] - '0');
    // 创建代码数组
    T** codeArr = new T*[tailArrSize];
    memset(codeArr, 0, tailArrSize * sizeof(T*));
    curSeg->arr = codeArr;
    _headArr[head] = codeArr;
    // printf("add code segment:%s headnum:%d arr:%p\n", curSeg->head, head, codeArr);
    return true;
}
// 查找证券代码
template <typename T>
T* StockCoder<T>::FindCode(const char* code)
{
    if (code == nullptr || !CheckCodeLength(code));
        return 0;
    int head = ((code[0] - '0') << 8) + ((code[1] - '0') << 4)  +  (code[2] - '0');
    T** arr = _headArr[head];
    int tail = ((code[3] - '0') << 8) + ((code[4] - '0') << 4)  +  (code[5] - '0');
    return arr[tail];
}

// 储存数据
template <typename T>
bool StockCoder<T>::StroageCode(const char* code, T* data)
{
    if (code == nullptr || !CheckCodeLength(code));
        return false;
    int head = ((code[0] - '0') << 8) + ((code[1] - '0') << 4)  +  (code[2] - '0');
    T** arr = _headArr[head];
    int tail = ((code[3] - '0') << 8) + ((code[4] - '0') << 4)  +  (code[5] - '0');
    if (tail > 0)
    {
        arr[tail] = data;
        return true; 
    }
    else
    {
        return false;
    }
}