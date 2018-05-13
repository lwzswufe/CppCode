
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

#include <fstream>
using std::ofstream; 

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <stdexcept>
using std::runtime_error;

void writelines_w(auto write_fn, const vector<string> &vector_string)
{   
    ofstream output;                        // 定义读取类
    output.open(write_fn, ofstream::out);   // 打开文件 w模式
    string line;

    for (string line: vector_string)
    {
        output << line;                     // 
        output << '\n';
    }
    //output << ends;                         // 会输出一个\0
    output.close();
}

void writelines_a(auto write_fn, const vector<string> &vector_string)
{   
    ofstream output;                        // 定义读取类
    output.open(write_fn, ofstream::app);   // 打开文件 a模式
    string line;

    for (string line: vector_string)
    {
        output << line;                     // 
        output << '\n';
    }
    output.close();
}

int main()
{   
    vector<string> vector_1{"one_line", "two_line", "three_line"};
    vector<string> vector_new{"new_line", "new_line"};
    string fn_1 = "write1.txt";             // c++11 支持string作为文件名
    char fn_2[20] = "write2.txt";           // c支持char数组
    writelines_w(fn_1, vector_1);
    writelines_w(fn_2, vector_1);
    writelines_a(fn_1, vector_new);
}