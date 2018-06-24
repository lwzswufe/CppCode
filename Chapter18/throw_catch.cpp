

#include <iostream>
using std::cout; using std::endl;

#include <exception>
using std::exception; using std::runtime_error; using std::logic_error;

#include <string>
using std::string;

struct rt_error: public runtime_error
{
public: rt_error(const string &s): runtime_error(s) {}   
};                                          // 构造函数

void f()
{
    throw rt_error("rt_error __");
}

int main()
{
    try
    {
        f();
    }
    catch (runtime_error &e)
    {                                       // e.what() 写出函数异常内容
        cout << "catch: " << e.what() << endl;
    }

    try
    {
        f();
    }
    catch (exception &e)
    {
        cout << "catch: " << e.what() << endl;
    }

    try
    {
        f();
    }
    catch (...)                             // 匹配所有的异常
    {
        cout << "catch_all " << endl;
    }
}