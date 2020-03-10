#include <memory>
#include <stdio.h>
#include <string.h>
#include <atomic>

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
    bool push(_Tp);
    // 读取数据
    _Tp pop();
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
    std::atomic<size_t> push_n{0};
    // 读取数
    std::atomic<size_t> pop_n{0};
    
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
    return push_n - pop_n;
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

// 写入数据value
template<typename _Tp>
bool CircularQueue<_Tp>::push(_Tp value)
{   
    if (size() >= capacity)
        return false;
    size_t idx = ++push_n;
    _arr[idx % capacity] = value;
    return true;
}

// 读取数据
template<typename _Tp>
_Tp CircularQueue<_Tp>::pop()
{
    if (pop_n < push_n)
    {   
        size_t idx = ++pop_n;
        return _arr[idx % capacity];
    }
    else
        return NULL;
}