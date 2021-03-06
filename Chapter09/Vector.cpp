
#include <vector>
using std::vector;

#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

void print(vector<auto> v)      // 输出字符串
{   
    cout << "vec: ";
    for(auto iter : v)
        cout << iter << ", ";
    cout << endl;
}

int main()
{   
    // 初始化
    vector<int> c_1(5);
    vector<int> c_2(5, 1);
    vector<int> c_3{2, 3, 5, 7, 11};                // 未赋值时值为0 
    vector<int> c_4(c_3);
    vector<int> c_5(c_3.begin(), c_3.end());
    bool cc;

    // cout << c_2 << endl;
    print(c_3);
    print(c_1);
    // 交换
    swap(c_1, c_3);

    print(c_3);
    print(c_1);

    // 比较
    print(c_2);
    print(c_3);
    cc =  c_2 < c_3;

    //插入 删除
    print(c_2);
    c_2.push_back(9);                   // 在尾部加入元素
    print(c_2);                     
    c_2.pop_back();                     // 在尾部删除元素
    print(c_2);
    // c_2.push_front(-1); vector不支持
    // print(c_2);
    // c_2.pop_front();
    // print(c_2);

    c_2.insert(++c_2.begin(), 3, 99);   // 在指定位置插入 n个元素
    print(c_2);
    c_2.insert(c_2.begin()+4,
               c_1.end()-2, c_1.end()); // 在指定位置插入 指定范围的元素
    print(c_2);   
    c_2.insert(c_2.begin(),{-1, -1});   // 在指定位置插入 元素值列表

    print(c_2);
    c_2.erase(c_2.begin());             // 删除指定位置元素
    print(c_2);                         // 删除指定范围元素
    c_2.erase(c_2.begin()+5, c_2.begin()+7);
    print(c_2);

    //访问元素
    print(c_4);

    auto val_front = c_4.front();       // 访问首元素
    cout << "front: " << val_front << endl;

    auto val_back = c_4.back();         // 访问尾元素
    cout << "back: " << val_back << endl;

    auto val = c_4.at(3);               // 安全随机访问 at
    val += 10;
    print(c_4);                         // 拷贝
    c_4.at(3) += 10;
    print(c_4);                         // 引用

    
    // 清空容器
    print(c_5);
    c_5.clear();
    print(c_5);

    // 属性
    cout << "size:" << c_4.size() << endl;
    cout << "max_size:" << c_4.max_size() << endl;
    cout << "is_empty:" << c_4.empty() << endl;

    // 仅适用于string vector
    cout << "capacity:" << c_4.capacity() << endl;  // 不扩容的情况下最大可支持容量    
    c_4.reserve(7);                                 // 扩容
    cout << "capacity:" << c_4.capacity() << endl;  // 不扩容的情况下最大可支持容量
    c_4.shrink_to_fit();                            // 去除未利用空间，减少分配空间到size
    cout << "capacity:" << c_4.capacity() << endl;  // 不扩容的情况下最大可支持容量

    return 0;
}