#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
int main()
{
    vector<string> vs {"231", "two", "three"};
    string* s_ptr = &vs[1];
    cout << *s_ptr << endl;
    vs.erase(vs.begin() + 1);       // 删除元素
    cout << *s_ptr << endl;         // s_ptr指向后一个元素
}