#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

int main()
{
    enum class Light {red, green, blue};    // 第一：声明Light为新的数据类型，称为枚举(enumeration);
                                            // 第二：声明red, green等为符号常量，通常称之为枚举量，
                                            // 其值默认分别为0-2
    Light color = Light::red;
    cout << static_cast<int>(color) << endl;
    cout << static_cast<int>(Light::blue) << endl;

    // cout << color << endl;              // 非法 enum class 不支持隐式类型转换

    enum class Trade                       // 显式定义枚举值
    {
        buy_open = 1,
        buy_cover = 2,
        sell_open = 3,
        sell_cover = 4,
    };
    cout << static_cast<int>(Trade::sell_open) << endl;

    enum Light2 {red, green, blue};         // 枚举值 red等在enum的作用域里
    int a1 = Light2::red;
    int a2 = green;
    Light2 a3 = Light2::blue;

    cout << a1 << endl;                     // enum支持隐式类型转换
    cout << a2 << endl;
    cout << a3 << endl;
    cout << blue << endl;
}