#include <memory>
#include <stdio.h>
#include <string.h>

// 循环队列类
template<typename _Tp>
struct CircularQueue
{
public:
    // 请为Queue分配2^N的大小
    CircularQueue(const size_t size);
    // 析构函数
    ~CircularQueue();
    // 写入数据
    void push(_Tp value);
    // 读取数据
    bool pop(_Tp& value);
    // 是否为空
    bool empty();
    // 显示
    void show();
    // 获取大小
    size_t size();
private:
    // 申请空间
    void _alloc(const size_t size);
    // 回收空间
    void _dealloc();
    // 第一条数据位置
    _Tp* _arr;
    // 容量
    size_t capacity;
    // 写入数
    size_t push_n;
    // 读取数
    size_t pop_n;
    
};

template<typename _Tp>
CircularQueue<_Tp>::CircularQueue(size_t size)
{
    _alloc(size);
    pop_n = 0;
    push_n = 0;
}

template<typename _Tp>
CircularQueue<_Tp>::~CircularQueue()
{
    _dealloc();
}

// 申请空间方法
template<typename _Tp>
void CircularQueue<_Tp>::_alloc(const size_t size)
{
    _arr = (_Tp*) malloc(sizeof(_Tp) * size);
    capacity = size;
}

// 释放方法
template<typename _Tp>
void CircularQueue<_Tp>::_dealloc()
{
    if (_arr != NULL)
        delete[] _arr;
    _arr = NULL;
    capacity = 0;
}

// 获取储存元素数目
template<typename _Tp>
size_t CircularQueue<_Tp>::size()
{   
    return capacity;
}

template<typename _Tp>
bool CircularQueue<_Tp>::empty()
{   
    return pop_n == push_n;
}

template<typename _Tp>
void CircularQueue<_Tp>::show()
{
    //printf("show____start:%p end:%p shift:%lu\n", start, end, shift_time);
}

// 写入数据
template<typename _Tp>
void CircularQueue<_Tp>::push(_Tp value)
{   
    _arr[push_n % capacity] = value;
    push_n++;
}

// 读取数据
template<typename _Tp>
bool CircularQueue<_Tp>::pop(_Tp& value)
{
    if (pop_n < push_n)
    {   
        value = _arr[pop_n % capacity];
        pop_n++;
        return true;
    }
    else
        return false;
}