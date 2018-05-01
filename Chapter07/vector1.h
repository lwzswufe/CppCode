// 定义Vector类
#include <string>
using std::string;

#include <stdio.h>

#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <cmath>


class Vector                                    // 类名
{   
public:                                         // 公有访问说明符
    double x, y, len;                           // 定义属性 
    Vector(double v1, double v2): x{v1}, y{v2}  // 构造函数 定义时初始化
    { cout << "use define fun 0" << endl;
      len = get_len();}
    Vector(double v1): x{v1}, y{v1}             // 构造函数 定义时初始化
    { cout << "use define fun 1" << endl;
      len = get_len();}
    // cout << " " << endl;                     // 不能在此处使用cout
    void show();                                // 成员函数 通过后面的内联函数定义   
    char* get_string();

private:                                        // 私有访问说明符
    const int dim{2};                           // 私有属性
    double get_len();                           // 私有方法
    
};                                              // end class 这里的分号不可省略

inline void Vector::show()                      // 使用内联函数定义类方法
{
    char *str_ptr;
    str_ptr = this->get_string();
    cout << str_ptr << endl;
}                

inline double Vector::get_len()
{   
    double l;
    l = sqrt(x * x + y * y);
    return l;
}

inline char* Vector::get_string()
{   
   char *str_ptr;
   sprintf(str_ptr, "*x: %.4f\ty: %.4f\tlen: %.4f", x, y, len);
   cout << str_ptr << endl;
   return str_ptr;
}     

ostream& operator<<(ostream& os, Vector& v)
{   
    // auto str_ptr = v.get_string();
    //str_ptr = v.get_string();
    os << "exit ";
};