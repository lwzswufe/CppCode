/*
* 智能指针
*
*/

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

#include <memory>
using std::shared_ptr;using std::make_shared;

#define print(x) cout << #x << ": " << x << endl; 
#define prints(x, y) cout << #x << ": " << x << endl << #y << ": " << y << endl;


struct A
{
    int x;
    double y;
    char z[8];
};
int main()
{
    shared_ptr<string> p1;
    shared_ptr<int> p2;
    shared_ptr<string> p3 = make_shared<string>(10, '9');
    shared_ptr<int> p4 = make_shared<int> (42);
    shared_ptr<int> p6;
    shared_ptr<int> p8 = make_shared<int> (99); // 用new分配内存

    vector<int> vec{1, 2, 3, 4};

    if (p1) 
        cout << "p1 is empty" << endl;
    else
        cout << "p1 is not empty" << endl;
    

    //print(*p1);  // p1为空 不可解引用          // 空指针指向0
    prints(p4, p2);

    print(p4.unique());                         // 引用计数是否为1
    p2 = p4;                                    // 共享变量
    print(p4.unique());                         // 引用计数是否为1

    prints(p4, p2);

    *p2 += 100;                                 // p2 p4指向同一个对象
    prints(*p2, *p4);

    print(p4.use_count());                      //引用计数+1
    p6 = p4;
    print(p4.use_count());
    print(p2.use_count());

    p6.reset();                                 // 析构p6 引用计数-1
    prints(p6, p4);                             // p4 p2不受影响
    print(p2.use_count());

    //int x = new int(10);
    int *new_p1 = new int(10);
    int *new_p2 = new int();
    int *new_p3 = new int(-546);
    const int *cnew_p4 = new const int(7);

    new_p2 = p6.get();                          // 提供get方法获取 new int型指针
    prints(p6, p8);
    p6.reset(new_p1);                           // 这里需要传入 new int型指针
    prints(p6, p8);

    print(new_p2);
    print(new_p3);
    cout << "delete" << endl;
    delete new_p3;                              // 释放内存
    delete cnew_p4;                             // 删除const指针
    //delete new_p2;
    //delete p6;  // 不能删除 shared_ptr
    print(new_p3);
    print(*new_p3);                             // 内存被释放 会输出乱码
    //int * norm_ptr = new int ();
    //norm_ptr = p2.get();
    
    prints(p1, p3); 
    p1 = move(p3);                              // 交换p1 p3指针指向的位置
    prints(p1, p3);
    p1.swap(p3);
    prints(p1, p3);                             // 交换p1 p3指针指向的位置

    cout << "over" << endl;
    //p1 = "hi";
    //*p1 = "hi";
    //cout << *p1 << endl;

    shared_ptr<A> pa = make_shared<A>();
    // 直接修改pa对应的数据
    sprintf((char*)pa.get() + 16, "%06d", 1547);
    // memset(pa, 0, sizeof(A));
    cout << "size struct A :" << sizeof(A) << endl
         << "size shared_ptr :" << sizeof(pa) << endl
         << "size *shared_ptr :" << sizeof(*pa) << endl
         << "x=" << pa->x << endl 
         << "y=" << pa->y << endl
         << "z=" << pa->z << endl
         << "ref: " << pa.use_count() << endl;
    shared_ptr<const A> pc = pa;
    cout << "ref: " << pa.use_count() << ", " << pc.use_count() << endl;
    pa.reset();                 // 释放pa
    cout << "ref: " << pa.use_count() << ", " << pc.use_count() << endl;
    pc.reset();
    cout << "ref: " << pa.use_count() << ", " << pc.use_count() << endl;
    return 0;
}
