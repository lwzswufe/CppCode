#include <memory>
#include <stdio.h>
#include <string.h>

// 序列数据类
template<typename _Tp>
struct Series
{
public:
    // 指定数量 值 创建序列对象
    Series(const size_t size_, const _Tp &value);
    // 指定数量 值 创建序列对象
    Series(const _Tp &value);
    // 默认构建方法
    Series();
    // 释放方法
    ~Series();
    // 拷贝构造 浅拷贝当前指针偏置 当前偏置值
    Series(const Series<_Tp>&);
    // 拷贝赋值
    void operator=(const Series<_Tp>&)=delete;
    // 首元素赋值
    void operator=(const _Tp &a);
    // 转换数据将数据延后 t期 返回偏置后的序列
    Series<_Tp>& operator[](const size_t t);
    // 隐式类型变换
    operator _Tp();
    // 在尾部增加变量
    void insert(const _Tp value);
    // 从尾部开始访问第idx访问
    _Tp& at(const size_t idx);
    // 获取大小 储存数据的数量
    size_t size() const;
    // 获取储存空间大小
    size_t capacity() const;
    // 设置最大储存空间
    void setMaxSize(const size_t size_);
    // 预分配空间
    void reserve(const size_t size_);
    // 是否为空
    bool empty() const;
    // 输出信息
    void show();
    // 
protected:
    // 初始化
    void init(); 
    // 分配空间 会创建一个略大于size的2^n
    void _alloc(const size_t size_);
    // 分配空间 若一开始未分配 分配size=4 肉一开始分配了 分配size=当前size*2
    void _alloc();
    // 释放空间 释放地址为 begin的空间
    void _dealloc(const _Tp* begin);
    // 清楚最早的size个数据
    void clear(const size_t num);
    // 起始元素位置
    _Tp* _start;
    // 元素结束位置
    _Tp* _end;
    // 当前元素位置
    _Tp* _cur;
    // 偏置时区数目
    size_t _offset;
    // 最大储存空间
    size_t _maxSize;
    // 是否是拷贝
    bool is_copy;
};


template<typename _Tp>
void Series<_Tp>::init()
{
    is_copy = false;
    _offset = 0;
}

template<typename _Tp>
Series<_Tp>::Series(const size_t size_, const _Tp &value)
{
    _alloc(size_);
    init();
    _cur = _end;
    for (size_t i=0; i<size_; i++)
    {   
        _cur--;
        *(_cur) = value;
    }
}

// 指定数量 值 创建序列对象
template<typename _Tp>
Series<_Tp>::Series(const _Tp &value)
{
    _alloc(1);
    *_cur = value;
    _cur--;
    init();
}

// 默认构建方法
template<typename _Tp>
Series<_Tp>::Series()
{
    _alloc(1);
    memset(_start, 0, sizeof(_Tp));
    init();
}

// 赋值构造函数 浅拷贝
template<typename _Tp>
Series<_Tp>::Series(const Series<_Tp>& ser)
{   
    memcpy(this, &ser, sizeof(Series<_Tp>));
    is_copy = true;
    _cur += _offset;
        if (_cur >= _end)
            _cur = _end - 1;
    _offset = 0;
}

// 释放方法
template<typename _Tp>
Series<_Tp>::~Series()
{   
    if (!is_copy)
    {
        _dealloc(_start);
        _start = NULL;
        _end = NULL;
        _cur = NULL;
    }
}

// 申请空间方法
template<typename _Tp>
void Series<_Tp>::_alloc(const size_t size_)
{
    _start = (_Tp*) malloc(sizeof(_Tp) * size_);
    _cur = _start + size_ - 1;
    _end = _start + size_;
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

template<typename _Tp>
void Series<_Tp>::reserve(const size_t size_)
{
    const _Tp* old_start = _start;
    const size_t old_size = capacity();
    const size_t ele_num = size();
    // 分配新空间 更新start stroage_end
    _alloc(size_);
    // 0初始化
    memset(_start, 0, sizeof(_Tp) * size_);
    // 复制原有数据到新空间
    memcpy(_end-old_size, old_start, sizeof(_Tp) * old_size);
    // 更新end
    _end = _start + size_;
    _cur = _end - ele_num;
    // 释放原有空间
    _dealloc(old_start);
}

// 从尾部开始访问第idx访问
template<typename _Tp>
_Tp& Series<_Tp>::at(const size_t idx)
{   
    // 越界检查
    _Tp* ptr = _cur + idx;
    if (ptr < _end)
        return *ptr;
    else 
        return *(_end - 1);
}

// 增加元素
template<typename _Tp>
void Series<_Tp>::insert(const _Tp value)
{   
    // 储存空间是否已满
    if (_cur <= _start)
    {   
        size_t cur_size = size();
        if (_maxSize == 0 || cur_size * 2 < _maxSize)
        {
            reserve(cur_size * 2);
        }
        else if (cur_size < _maxSize)
        {   
            reserve(_maxSize);
        }
        else
        {   // 清除最早的一半数据
            clear(cur_size / 2);
        }
    }
    // 当前指针迭代
    _cur--;
    // 当前指针赋值
    *_cur = value;
}

// 获取储存元素数目
template<typename _Tp>
size_t Series<_Tp>::size() const
{   
    return _end - _cur;
}

// 获取储存空间大小
template<typename _Tp>
size_t Series<_Tp>::capacity() const
{
    return _end - _start;
}

// 首元素赋值
template<typename _Tp>
void Series<_Tp>::operator=(const _Tp &value)
{   
    if (_offset == 0)
        *_cur = value;
    else
    {   
        _Tp* ptr = _cur + _offset;
        if (ptr >= _end)
            ptr = _end - 1;
        *ptr = value; 
        _offset = 0;
    }
    
}

// 转换数据将数据延后 t期 返回偏置后的序列
template<typename _Tp>
Series<_Tp>& Series<_Tp>::operator[](size_t t)
{   
    // printf("[%lu] _start:%p _end:%p\n", t, _start, _end);
    _offset = t;
    return *this;
}

// 隐式类型变换
template<typename _Tp>
Series<_Tp>::operator _Tp()
{   
    if (_offset == 0)
    {   
        // printf("_start:%p _end:%p shift:%lu\n", _start, _end, _offset);
        return *_cur;
    }
    else
    {   
        _Tp* ptr = _cur + _offset;
        // 边界检查
        if (ptr >= _end)
            ptr = _end - 1;
        _offset = 0;
        // printf("_start:%p _end:%p shift:%lu\n", _start, _end, _offset);
        return *ptr;
    }
}

// 设置最大储存空间
template<typename _Tp>
void Series<_Tp>::setMaxSize(const size_t size_)
{
    _maxSize = size_;
}

// 是否为空
template<typename _Tp>
bool Series<_Tp>::empty() const
{   
    return _end == _start;
}

template<typename _Tp>
void Series<_Tp>::show()
{
    printf("show____start:%p _end:%p shift:%lu\n", _start, _end, _offset);
}

template<typename _Tp>
void Series<_Tp>::clear(const size_t num)
{   
    size_t clear_num, residual_num;
    if (num < size())
    {
        clear_num = num;
        residual_num = size() - clear_num;
        _Tp temp[residual_num];
        memcpy(_cur, temp, sizeof(_Tp) * residual_num);
        memset(_cur, 0, sizeof(_Tp) * clear_num);
        _cur = _end - residual_num - 1;
        memcpy(temp, _cur, sizeof(_Tp) * residual_num);
    }
    else
    {
        clear_num = size();
        memset(_cur, 0, sizeof(_Tp) * clear_num);
        _cur = _end - 1;
    }
}