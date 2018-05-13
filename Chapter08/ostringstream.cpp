#include <iostream>
using std::cin; using std::cout; using std::cerr;
using std::istream; using std::ostream; using std::endl;

#include <sstream>
using std::ostringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

int main()
{   
    vector<string> vec_name{"morgan",
                            "drew",
                            "lee"};
    vector<int> vec_phone{123456,
                          4577318,
                          26865735};

    const int len=vec_name.size();

    ostringstream str_out;                              // 声明输出对象

    for (int i=0;i<len;i++)
    {   
        str_out << vec_name[i] << ": ";
        str_out << vec_phone[i];                        // 输出字符串
        str_out.put('\n');                              // 输出字符
    }
    cout << "write over" << endl;
    cout << str_out.str() << endl;                      // 输出
    return 0;
}