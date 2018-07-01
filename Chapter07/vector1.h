// 定义Vector类
#include <string>
using std::string;

#include <cstdio>

#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <cmath>


class Vector                                    // 类名
{   
public:                                         // 公有访问说明符
    double x, y, len;                           // 定义属性 
    friend string get_string(Vector &);         // 友元声明 声明后 get_string即可获得private权限

    Vector() = default;                         // 默认构造函数

    Vector(double v1, double v2): x{v1}, y{v2}  // 构造函数 定义时初始化
    { cout << "use define fun 0" << endl;
      len = get_len();
    }
    Vector(double v1): x{v1}, y{v1}             // 构造函数 定义时初始化
    { cout << "use define fun 1" << endl;
      len = get_len();
    }
    // cout << " " << endl;                     // 不能在此处使用cout
    void show();                                // 成员函数 通过后面的内联函数定义
    string get_string2(); 
    

private:                                        // 私有访问说明符
    const int dim{2};                           // 私有属性
    double get_len();                           // 私有方法
    
};                                              // end class 这里的分号不可省略

inline void Vector::show()                      // 使用内联函数定义类方法
{
    cout << this->get_string2() << endl;
}                

inline double Vector::get_len()
{   
    double l;
    l = sqrt(x * x + y * y);
    return l;
}

inline string Vector::get_string2()
{   
    string str;
    char char_arr[30];
    sprintf(char_arr, "x: %.4f\ty: %.4f\tlen: %.4f", x, y, len);
    str = char_arr;
    return str;
}     

ostream& operator<<(ostream& os, Vector& v)        // 重载 << 运算符
{   
    cout << "Vector:\n" 
         << get_string(v)
         << "  "
         << endl;
    cout << "overload <<";
};

string get_string(Vector& v)
{   
    string str;
    char char_arr[30];
    sprintf(char_arr, "x: %.4f\ty: %.4f\tlen: %.4f", v.x, v.y, v.get_len());
    str = char_arr;
    return str;
}     