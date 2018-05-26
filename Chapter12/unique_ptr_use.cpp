
#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

#include <string> 
using std::string;

#include <memory>
using std::shared_ptr;using std::unique_ptr;

#define print(x) cout << #x << ": " << x << endl; 

unique_ptr<int> f1(unique_ptr<int> p)
{
    ++*p;
    return p;
}

void f2(const unique_ptr<int>& p)
{
    ++*p;
}

int main() 
{   
    unique_ptr<int> p{new int(7)};
    unique_ptr<int> p2{new int()};
    print(*p);
    // 错误用法 p = f1(p);   // 因为unique_ptr不可拷贝
    p = f1(move(p));        // p重置->值被转移给临时变量->函数结束临时变量销毁->临时变量被拷贝给p
    print(*p);
    f2(p);
    print(*p);
    return 0;
}

