//默认参数
#include <iostream>
using std::cout; using std::endl; using std::cerr;

#include <cassert>

#include <string>
using std::string;

#include <cstddef>
using std::size_t;

// #define NDEBUG         // 开启/关闭debug模式

void print(size_t size)
{
#ifndef NDEBUG
#ifdef FUNC_CPP
// __func__ is a local static defined by the compiler that holds the name of this function
cerr << __func__ << ": array size is " << size << endl;
#else
// if __func__ isn't defined yet, use nonstandard MS equivalent __FUNCTION__ variable
cerr << __FUNCTION__ << ": array size is " << size << endl;
#endif  // FUNC_CPP
#endif  // NDEBUG
// . . .
}

int main()
{   
#ifdef NDEBUG
    cout << "define NDEBUG    close debug" <<endl;
#else
    cout << "No define NDEBUG open  debug" <<endl;
#endif
    print(0);
    int a = 1;
    double c = 1;

    assert(a == c);                      // 定义NDEBUG会关闭调试状态 使assert无效

    cout <<   "filename: " << __FILE__
         << "\nline_num: " << __LINE__
         << "\nCompiled: " << __DATE__
         << "\ntime    : " << __TIME__
         << "\nfun_name: " << __func__
         << endl;
    return 0;
}