// 定义Vector类
#include <string>
using std::string;

#include <stdio.h>

#include <iostream>
using std::cout; using std::endl; using std::ostream; using std::istream;

#include <cmath>


class Vector                                    // 类名
{   
public:                                         // 公有访问说明符
    double x, y;                                // 定义属性 

    Vector() = default;                         // 默认构造函数

    Vector(double v1, double v2): x{v1}, y{v2}  // 构造函数 定义时初始化
    { cout << "use define fun 0" << endl;}

    Vector(double v1): x{v1}, y{v1}             // 构造函数 定义时初始化
    { cout << "use define fun 1" << endl;}

    Vector(const Vector &vec): x{vec.x}, y{vec.y}     // 构造函数 定义时初始化
    { cout << "use define fun 2" << endl;}

    Vector(const Vector &&v): x{v.x}, y{v.y}    // 构造函数 定义时初始化
    { cout << "use define fun 3" << endl;}

    Vector &operator=(const Vector&);
    Vector &operator=(const Vector&&);
    Vector &operator+=(const Vector&);
    Vector &operator-=(const Vector&);
    Vector &operator*=(int);
    Vector &operator*=(double);

    ~Vector() {cout << "delete" << endl;};
    void show();                                // 成员函数 通过后面的内联函数定义
    string get_string(); 
    string get_short_string();

private:                                        // 私有访问说明符
    const int dim{2};                           // 私有属性
    double get_len();                           // 私有方法
    
};                                              // end class 这里的分号不可省略

inline void Vector::show()                      // 使用内联函数定义类方法
{
    cout << this->get_string() << endl;
}                

inline double Vector::get_len()
{   
    double len;
    len = sqrt(x * x + y * y);
    return len;
}

inline string Vector::get_string()
{   
    char char_arr[30];
    sprintf(char_arr, "x: %.4f\ty: %.4f\tlen: %.4f", x, y, get_len());
    string str = char_arr;
    return str;
}     

inline string Vector::get_short_string()
{   
    char char_arr[30];
    sprintf(char_arr, "x: %.4f\ty: %.4f\t", x, y);
    string str = char_arr;
    return str;
}     

inline 
Vector& Vector::operator=(const Vector &v)
{
    x = v.x;
    y = v.y;
    return *this;
}

inline 
Vector& Vector::operator=(const Vector &&v)
{
    x = v.x;
    y = v.y;
    return *this;
}

inline 
Vector& Vector::operator+=(const Vector &v) // 重载 += 运算符
{
    x += v.x;
    y += v.y;
    return *this;
}

inline 
Vector& Vector::operator-=(const Vector &v) // 重载 -= 运算符
{
    x += v.x;
    y += v.y;
    return *this;
}

inline 
Vector& Vector::operator*=(int alpha)       // 重载 *= 运算符
{
    x *= alpha;
    y *= alpha;
    return *this;
}

inline 
Vector& Vector::operator*=(double alpha)    // 重载 *= 运算符
{
    x *= alpha;
    y *= alpha;
    return *this;
}

ostream& operator<<(ostream& os, Vector& v) // 重载 << 运算符
{   
    string str = v.get_short_string();
    cout << "Vector:\n" 
         << str;
    return os;
};

Vector operator+(const Vector& v1, const Vector& v2)// 重载 + 运算符
{   
    Vector v(v1.x + v2.x, v1.y + v2.y);
    return v;
};

Vector operator-(const Vector& v1, const Vector& v2)// 重载 - 运算符
{   
    Vector v(v1.x - v2.x, v1.y - v2.y);
    return v;
};

Vector operator*(const Vector& v1, double alpha)    // 重载 * 运算符
{   
    Vector v(v1.x * alpha, v1.y * alpha);
    return v;
};

Vector operator*(const Vector& v1, int alpha)       // 重载 * 运算符
{   
    Vector v(v1.x * alpha, v1.y * alpha);
    return v;
};

bool operator==(const Vector& v1, const Vector& v2) // 重载 == 运算符
{   
    bool b = (v1.x==v2.x) & (v2.y == v2.y);
    return b;
};

bool operator!=(const Vector& v1, const Vector& v2) // 重载 != 运算符
{   
    bool b = v1 == v2;
    return ~b;
};
