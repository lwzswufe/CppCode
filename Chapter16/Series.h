#include <memory>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
using std::runtime_error;
#pragma once

class SeriesError :public runtime_error
{
public: SeriesError(const char* s) : runtime_error(s) {}
};


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
    void operator=(const Series<_Tp>& ser);
    // 首元素赋值
    void operator=(const _Tp &value);
    // 转换数据将数据延后 t期 返回偏置后的序列
    _Tp operator[](size_t t) const;
	// 转换数据将数据延后 t期 返回偏置后的序列
	_Tp operator[](int t) const;
	// 转换数据将数据延后 t期 返回偏置后的序列
	_Tp operator[](double t) const;
    // 转换数据将数据延后 t期 返回偏置后的序列
	Series<_Tp> operator()(size_t t);
    // 比较
    bool operator==(const _Tp &value);
    // 比较
    bool operator!=(const _Tp &value);
    // 大于
    bool operator>(const _Tp &value);
    // 小于
    bool operator<(const _Tp &value);
    // 大于等于
    bool operator>=(const _Tp &value);
    // 小于等于
    bool operator<=(const _Tp &value);
    // 隐式类型变换
    operator _Tp();
    // 在尾部增加变量
    void insert(const _Tp value);
    // 从尾部开始访问第idx访问
    _Tp& at(const size_t idx) const;
    // 获取大小 储存数据的数量
    size_t size() const;
    // 获取大小 储存数据的数量
    int length() const;
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
protected:
    // 初始化
    void init(); 
    // 分配空间 会创建一个略大于size的2^n
    void _alloc(const size_t size_);
    // 分配空间 若一开始未分配 分配size=4 肉一开始分配了 分配size=当前size*2
    void _alloc();
    // 释放空间 释放地址为 begin的空间
    void _dealloc(const _Tp* begin);
    // 清除最早的size个数据
    void clear(const size_t num);
	// 清除最早的size个数据
	void clear(const double num);
    // 起始元素位置
	_Tp* _start{nullptr};
    // 元素结束位置
    _Tp* _end{ nullptr };
    // 当前元素位置
    _Tp* _cur{ nullptr };
    // 最大储存空间
	size_t _maxSize{0};
    // 是否是拷贝
	bool is_copy{false};
    // 是否是引用
	bool is_ref{false};
};


template<typename _Tp>
void Series<_Tp>::init()
{
    is_copy = false;
}

template<typename _Tp>
Series<_Tp>::Series(const size_t size_, const _Tp &value)
{
    _alloc(size_);
    init();
    for (size_t i=0; i<size_; i++)
    {   
        insert(value);
    }
}

// 指定数量 值 创建序列对象
template<typename _Tp>
Series<_Tp>::Series(const _Tp &value)
{
    _alloc(1);
    insert(value);
    init();
}

// 默认构建方法
template<typename _Tp>
Series<_Tp>::Series()
{
    init();
}

// 赋值构造函数 浅拷贝
template<typename _Tp>
Series<_Tp>::Series(const Series<_Tp>& ser)
{   
    memcpy(this, &ser, sizeof(Series<_Tp>));
    is_copy = true;
    if (_cur >= _end)
        _cur = _end;
}

// 释放方法
template<typename _Tp>
Series<_Tp>::~Series()
{   
    if (!is_copy && !is_ref )
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
    _cur = _start + size_;
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
    if (begin != nullptr)
        delete[] begin;
}

template<typename _Tp>
void Series<_Tp>::reserve(const size_t size_)
{	
	size_t cur_size = size();
    const _Tp* old_start = _start;
    const _Tp* old_cur = _cur;
    size_t copy_num;
	if (size_ > cur_size)
	{
		cur_size = size_;
	}
    if (size_ > size())
        copy_num = size();
    else
        copy_num = size_;
    // 分配新空间 更新start stroage_end
    _alloc(size_);
    // 0初始化
    memset(_start, 0, sizeof(_Tp) * size_);
    // 复制原有数据到新空间
    if (copy_num > 0)
    {
        memcpy(_end-copy_num, old_cur, sizeof(_Tp) * copy_num);
    }
    // 更新end
    _end = _start + size_;
    _cur = _end - copy_num;
    // 释放原有空间
    _dealloc(old_start);
}

// 从_cur开始访问第idx元素访问
template<typename _Tp>
_Tp& Series<_Tp>::at(const size_t idx) const
{   
    // 越界检查
    _Tp* ptr = _cur + idx;
    if (ptr < _end)
        return *ptr;
    else 
    {
        char s[256];
        sprintf(s, "Series size:%lu capacity:%lu idx:%lu out of range\n", 
                size(), capacity(), idx);
        throw SeriesError(s);
    }
}

// 增加元素
template<typename _Tp>
void Series<_Tp>::insert(const _Tp value)
{   
    // 储存空间是否已满
    if (_cur <= _start)
    {   
        size_t cur_size = capacity();
        if (cur_size == 0)
        {
            reserve(1);
        }
        else if (cur_size < _maxSize)
        {   
            if (cur_size * 2 < _maxSize)
            {
                reserve(cur_size * 2);
            }
            else
            {
                reserve(_maxSize);
            }
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

// 获取储存元素数目
template<typename _Tp>
int Series<_Tp>::length() const
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
    if (empty())
    {   
        throw SeriesError("Series is empty\n");
    }
    *_cur = value;
}

template<typename _Tp>
void Series<_Tp>::operator=(const Series<_Tp>& ser)
{   
    if (empty() || ser.empty())
    {   
        throw SeriesError("Series is empty\n");
    }
	*_cur = ser.at(0);
}

// 随机访问
template<typename _Tp>
_Tp Series<_Tp>::operator[](size_t t) const
{   
    if (empty())
    {   
        return _Tp{0};
    }
    return *(this->_cur + t);
}

// 随机访问
template<typename _Tp>
_Tp Series<_Tp>::operator[](int t) const
{   
    if (empty())
    {   
        return _Tp{0};
    }
	return operator[](static_cast<size_t>(t));
}

// 随机访问
template<typename _Tp>
_Tp Series<_Tp>::operator[](double t) const
{   
    if (empty())
    {   
        return _Tp{0};
    }
	return operator[](static_cast<size_t>(t));
}

// 随机访问
template<typename _Tp>
Series<_Tp> Series<_Tp>::operator()(size_t t)
{   
    if (t == 0)
    {
        return *this;
    }
    Series<_Tp> _copy = *this;
    _copy._cur += t;
    if (_copy._cur > _copy._end)
    {
        _copy._cur = _copy._end--;
    }
	return _copy;
}

// 比较
template<typename _Tp>
bool Series<_Tp>::operator==(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur == value;
}


// 比较
template<typename _Tp>
bool Series<_Tp>::operator!=(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur == value;
}

// 大于
template<typename _Tp>
bool Series<_Tp>::operator>(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur > value;
}
// 小于
template<typename _Tp>
bool Series<_Tp>::operator<(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur < value;
}

// 大于等于
template<typename _Tp>
bool Series<_Tp>::operator>=(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur >= value;
}
// 小于等于
template<typename _Tp>
bool Series<_Tp>::operator<=(const _Tp &value)
{
    if (empty())
        return false;
    else 
        return *_cur <= value;
}
// 隐式类型变换
template<typename _Tp>
Series<_Tp>::operator _Tp()
{   
    // printf("_start:%p _end:%p shift:%lu\n", _start, _end, _offset);
    return *_cur;
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
    return _cur == _end;
}

template<typename _Tp>
void Series<_Tp>::show()
{
    printf("Series:%p cur:%p start:%p end:%p\n", this, _cur, _start, _end);
}

template<typename _Tp>
void Series<_Tp>::clear(const double num)
{
	clear(static_cast<size_t>(num));
}

template<typename _Tp>
void Series<_Tp>::clear(const size_t num)
{   
    size_t clear_num;
    if (num < size())
    {
        clear_num = num;
        const size_t residual_num = this->size() - clear_num;
#ifdef _WIN32
		_Tp* temp = new _Tp[residual_num];
#else	
		_Tp temp[residual_num];
#endif
        memcpy(temp, _cur, sizeof(_Tp) * residual_num);
        memset(_cur, 0, sizeof(_Tp) * clear_num);
        _cur = _end - residual_num;
        memcpy(_cur, temp, sizeof(_Tp) * residual_num);
#ifdef _WIN32
		delete[] temp;
#endif 
    }
    else
    {
        clear_num = size();
        memset(_cur, 0, sizeof(_Tp) * clear_num);
        _cur = _end - 1;
    }
}