
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

#include <fstream>
using std::ifstream; 

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <stdexcept>
using std::runtime_error;

void readlines_for(auto read_fn, vector<string> &vector_string)
{   
    ifstream input;                         // 定义读取类
    input.open(read_fn);                    // 打开文件
    string line;

    for (int i=0; i<3; i++)
    {
        getline(input, line);               // getline 会自动删除\n
        vector_string.push_back(line);
    }
    input.close();
}

void readlines_while(auto read_fn, vector<string> &vector_string)
{   
    ifstream input;                         // 定义读取类
    input.open(read_fn);                    // 打开文件
    string line;

    while(!input.eof())
    {
        getline(input, line);               // getline 会自动删除\n
        vector_string.push_back(line);
        cout << "read:      " << line         << endl;
        cout << "io.good(): " << input.good() << endl;  // 操作成功
        cout << "io.eof(): "  << input.eof()  << endl;  // 到达末尾
        cout << "io.fail(): " << input.fail() << endl;  // 操作失败
        cout << "io.bad(): "  << input.bad()  << endl;  // 操作失败（严重）
    }
    cout << "到达文件末尾会触发 io.eof() 与 io.fail()" << endl;
    input.close();
}

int main()
{   
    vector<string> vector_1, vector_2;
    string read_fn_1 = "read.txt";          // c++11 支持string作为文件名
    char read_fn_2[9] = "read.txt";         // c支持char数组

    readlines_for(read_fn_1, vector_1);
    readlines_for(read_fn_2, vector_2);

    readlines_while(read_fn_1, vector_1);

    for (auto s : vector_1)
    {
        cout << s << endl;
    }

    for (auto s : vector_2)
    {
        cout << s << endl;
    }

    return 0;
}