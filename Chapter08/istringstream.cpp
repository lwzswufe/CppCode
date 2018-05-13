#include <iostream>
using std::cin; using std::cout; using std::cerr;
using std::istream; using std::ostream; using std::endl;

#include <sstream>
using std::istringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

int main()
{   
    string str_1{"morgan 2015552368 8625550123\n"
                 "drew 9735550130\n"
                 "lee 6095550132 2015550175 8005550000\n"};
    string line;
    const char  seq{' '};
    char chr;
    char name[20], phone[60];
    istringstream str_in(str_1);

    while (getline(str_in, line))
    {   
        istringstream line_in;
        line_in.str(line);
        line_in.get(name, 20, seq);              // 获取最大长度20 分隔符为seq的char[]到name
        cout << "name: " << name << endl;        // 读取分隔符 不读取的话会循环卡在分隔符这里

        while(!line_in.eof())
        {
            line_in.get(chr);                    // 读取分隔符 不读取的话会循环卡在分隔符这里
            line_in.get(phone, 60, seq);
            cout << "phone: " << phone << endl;
        } 
    }
    return 0;
}