#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

struct Address
{
    const char* name;       // 姓名
    const long phone;       // 手机
    const int zip_code;     // 邮编
    const char* addr;       // 住址
};                          // 类定义完毕后记得加;

void print_addr(Address* p)
{
    cout << p->name <<  "\n" <<
            p->phone << "\n" <<
            p->zip_code << "\n" <<
            p->addr << "\n" <<
    endl;
}

void print_addr(const Address& a)
{
    cout << a.name <<  "\n" <<
            a.phone << "\n" <<
            a.zip_code << "\n" <<
            a.addr << "\n" <<
    endl;
}

struct Field               // 定义 域 域内部只能有枚举与整型
{
    bool define: 1;
    int num: 127;
};                          // 类定义完毕后记得加;

int main()
{   
    Address addr_1 = {"Jim", 1223456, 31246, "nabdajbhvjvd"};
    // print_addr(addr_1);  // 类不会自动转化为指针
    print_addr(&addr_1);    // 传递指针
    print_addr(addr_1);     // 传递引用
    Field f;
    cout << f.define << '\n'// 访问域
         << f.num << '\n'
         << endl;
}