#include<iostream>

using namespace std;
using std::cout; using std::endl; using std::string;

int main()
{
    string st("The expense of spirit\n");
    for (char c : st)   // only for c++11
    {   
        cout << c;      // cout 仅输出到缓存区
        c = toupper(c); // 这里的c是拷贝 不会改变原有的值
    }
    cout << " endline" << endl;// endl将缓存区数据输出
    cout << st << endl;
    for (char &c : st)   // only for c++11
    {
        c = toupper(c);  // 这里的c是引用 会改变原有的值
    }
    cout << st << endl;
}
    