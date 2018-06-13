#include <iostream>
using std::ostream; 
using std::cout;

template <typename T>
ostream& print(ostream &os, const T &t)
{   
    os << "final ";
    return os << t;
}

template <typename T, typename... Args>
ostream& print(ostream &os, const T &t, const Args&... rest)
{   
    os << t << ", ";
    return print(os, rest...);          // 递归调用
}

int main()
{   
    print(cout, "001", "002", "003");
}
