// 定义Vector类
#include <string>
#include <iostream>
using std::cout; using std::endl;

class Vector                                // 类名
{   
    int x, y;                               // 定义属性
public:                                     // 公有访问说明符
    Vector(int v1, int v2): x{v1}, y{v2} { }// 构造函数
	
    void show()                             // 成员函数
    {
        cout << "x: " << x 
             << ",  y: " << y 
             << endl;
    }                                       // end show
};                                          // end class 这里的分号不可省略