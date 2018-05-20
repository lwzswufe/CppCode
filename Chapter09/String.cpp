
#include <string>
using std::string;

#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

int main()
{   
    const char* cp = "Hello World!";    //
    string s(cp);
    string s1(cp, 5);                   // 从cp开始取5个字符
    string s2(cp+6, 5);
    string s3(cp+5, 10);                // 从cp+5开始取最多10个字符

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

    string sub1 = s.substr(0, 5);       // 拷贝从0开始的 5个字符
    string sub2 = s.substr(6);          // 拷贝从0开始的    字符
    string sub3 = s.substr(6, 11);      // 拷贝从0开始的 最多11个字符

    cout << sub1 << endl;
    cout << sub2 << endl;
    cout << sub3 << endl;

    cout << s << endl;
    s.insert(s.size(), 5, '!');         // 在末尾增加5个感叹号
    cout << s << endl;          
    s.erase(s.size()-5, 5);             // 从末尾-5开始删除5个数字
    cout << s << endl;

    string s5{"I hear "};
    s.insert(0, s5);                    // 插入字符串
    cout << s << endl;

    s.replace(2, 4, "Hear");            // 指定位置开始的N个字符替换为另一个字符串
    cout << s << endl;

    s.append(" by C++");                // 在末尾添加字符串
    cout << s << endl;

    cout << s.compare(s2) << endl;      // 比较字符串大小
    return 0;
}