#include<type_traits>
#include<iostream>
using std::cout; using std::endl;

template<typename _Tp>
void print(_Tp v)
{   
    // 是否是指针类型
    if (std::is_pointer<_Tp>::value)
    {   
        // 是否是空指针
        if (std::is_null_pointer<decltype(v)>::value)
        {   
            cout << std::boolalpha << std::is_null_pointer<decltype(v)>::value << endl;
            cout << "nullptr" << endl;
            return;
        }
        // 移除指针修饰 获取被修饰的类型
        using remove_pointer_Tp = typename std::remove_pointer<_Tp>::type;
        // 被修饰的类型是否是 char
        if (std::is_same<remove_pointer_Tp, char>::value)
        {
            cout << v << endl;
        }
        // else if (std::is_arithmetic<remove_pointer_Tp>::value)
        // {
        //     remove_pointer_Tp to_v = *v;
        //     cout << to_v << endl;
        // }
    }
    // 是否是整数类型
    if (std::is_integral<_Tp>::value)
        cout << v << endl;
    // 是否是浮点数类型
    else if (std::is_floating_point<_Tp>::value)
        cout << v << endl;
} 

int main()
{
    print(0);
    print(1.1);
    char s[128]{"char abc"}, *ns{nullptr};
    const char cs[128] {"const char abc"};
    print(s);
    print(s);
    print(ns);
    return 0;
}