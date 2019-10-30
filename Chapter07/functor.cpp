#include <stdio.h>
#include <functional>
using std::binary_function;

template <class T>                          // 模板类型
struct Plus:public binary_function<T, T, T> // 继承binary_function STL基准类
{
    T operator()(const T& x, const T& y)
    {
        return x + y;
    }
};

int plus_(const int x, const int y)
{
    return x + y;
}

int main()
{
    int a=3, b=5;
    Plus<int> plus;
    printf("%d + %d = %d\n", a, b, plus(a, b));
    printf("%d + %d = %d\n", a, b, Plus<int>()(a, b));
    int (*fun)(const int x, const int y);
    fun = &plus_;
    printf("%d + %d = %d\n", a, b, fun(a, b));
}
