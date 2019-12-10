#include <memory>
#include <stdio.h>

// 序列数据类
template<typename _Tp>
struct Series
{
public:
    // 指定数量 值 创建序列对象
    Series(const size_t size, const _Tp value);
    // 指定数量 值 创建序列对象
    Series(const _Tp value);
    // 默认构建方法
    Series();
    // 释放方法
    ~Series();
    // 拷贝构造
    Series(const Series<_Tp>&);
    // 拷贝赋值
    void operator=(const Series<_Tp>&)=delete;
    // 首元素赋值
    void operator=(const _Tp &a);
    // 转换数据将数据延后 t期 返回偏执后的序列
    Series<_Tp>& operator[](const size_t t);
    // 隐式类型变换
    operator _Tp();
    // 在尾部增加变量
    void push_back(const _Tp);
    // 从尾部开始访问第idx访问
    _Tp& at(const size_t idx);
    // 获取大小 储存数据的数量
    size_t size() const;
    // 获取储存空间大小
    size_t capacity() const;
    // 是否为空
    bool empty() const;
protected:
    // 分配空间 会创建一个略大于size的2^n
    void _alloc(const size_t size);
    // 分配空间 若一开始未分配 分配size=4 肉一开始分配了 分配size=当前size*2
    void _alloc();
    // 释放空间 释放地址为 begin的空间
    void _dealloc(const _Tp* begin);
    // 起始元素位置
    _Tp* start;
    // 元素结束位置
    _Tp* end;
    // 已分配空间终点
    _Tp* stroage_end;
};

template<typename _Tp>
Series<_Tp>::Series(const size_t size, const _Tp value)
{
    _alloc(size);
    for (size_t i=1; i<=size; i++)
    {
        *end = value;
        end++;
    }
}

// 指定数量 值 创建序列对象
template<typename _Tp>
Series<_Tp>::Series(const _Tp value)
{
    _alloc();
    *start = value;
    end++;
}

// 默认构建方法
template<typename _Tp>
Series<_Tp>::Series()
{
    _alloc();
}

// 赋值构造函数
template<typename _Tp>
Series<_Tp>::Series(const Series<_Tp>& ser)
{
    _alloc(ser.capacity());
    memcpy(start, ser.start, ser.size() * sizeof(_Tp));
    end += ser.size();
}

// 释放方法
template<typename _Tp>
Series<_Tp>::~Series()
{
    _dealloc(start);
    start = NULL;
    end = NULL;
    stroage_end = NULL;
}

// 申请空间方法
template<typename _Tp>
void Series<_Tp>::_alloc(const size_t size)
{
    start = (_Tp*) malloc(sizeof(_Tp) * size);
    stroage_end = start + size;
    end = start;
}

// 申请空间方法
template<typename _Tp>
void Series<_Tp>::_alloc()
{   
    if (capacity() == 0)
        _alloc(4);
    else
        _alloc(capacity() * 2);
}

// 释放方法
template<typename _Tp>
void Series<_Tp>::_dealloc(const _Tp* begin)
{
    if (begin != NULL)
        delete begin;
}

// 从尾部开始访问第idx访问
template<typename _Tp>
_Tp& Series<_Tp>::at(const size_t idx)
{   
    // 越界检查
    if(end <= start)
        return *start;
    else
        return *(end - idx - 1);
}

// 在尾部增加变量
template<typename _Tp>
void Series<_Tp>::push_back(const _Tp value)
{
    if (end >= stroage_end)
    {
        const _Tp* old_start = start;
        size_t old_size = end - start;
        // 分配新空间 更新start stroage_end
        _alloc();
        // 复制原有数据到新空间
        memcpy(start, old_start, sizeof(_Tp) * old_size);
        // 更新end
        end = start + old_size;
        // 释放原有空间
        _dealloc(old_start);
    }
    // 尾元素赋值
    *end = value;
    // 指针迭代
    end++;
}

// 获取储存元素数目
template<typename _Tp>
size_t Series<_Tp>::size() const
{
    return end - start;
}

// 获取储存空间大小
template<typename _Tp>
size_t Series<_Tp>::capacity() const
{
    return stroage_end - start;
}

// 首元素赋值
template<typename _Tp>
void Series<_Tp>::operator=(const _Tp &a)
{
    *start = a;
}

// 转换数据将数据延后 t期 返回偏置后的序列
template<typename _Tp>
Series<_Tp>& Series<_Tp>::operator[](size_t t)
{   
    if (t == 0)
        return *this;
    else
    {
        std::unique_ptr<Series> shift_series = new Series;
        memcpy(shift_series, this, sizeof(Series));
        shift_series.end -= t;
        return *shift_series;
    }
}

// 隐式类型变换
template<typename _Tp>
Series<_Tp>::operator _Tp()
{
    return *(end - 1);
}

template<typename _Tp>
bool Series<_Tp>::empty() const
{   
    return end == start;
}