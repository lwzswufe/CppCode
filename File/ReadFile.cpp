/* FEOF example */
#include <cstdio>

#include<string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;

int demo(const char* filename)          // C语言风格
{   
   FILE * pFile;
   int buffer_size{100};
   char buffer [buffer_size];

   pFile = fopen (filename , "r");
   if (pFile == NULL) 
   {
       perror ("Error opening file");   // 输出异常
   }
   else
   {
     while ( ! feof (pFile) )
     {
       if ( fgets (buffer , buffer_size , pFile) == NULL ) break;
       fputs (buffer , stdout);         // 输出数据到 stddout
     }
     fclose (pFile);
   }
   return 0;
}


void readlines_while(const char* read_fn, vector<string> &vector_string)
{   
    ifstream input;                         // 定义读取类
    input.open(read_fn);                    // 打开文件
    string line;

    while(!input.eof())
    {
        getline(input, line);               // getline 会自动删除\n
        vector_string.push_back(line);
        // cout << "read:      " << line         << endl;
        // cout << "io.good(): " << input.good() << endl;  // 操作成功
        // cout << "io.eof(): "  << input.eof()  << endl;  // 到达末尾
        // cout << "io.fail(): " << input.fail() << endl;  // 操作失败
        // cout << "io.bad(): "  << input.bad()  << endl;  // 操作失败（严重）
    }
    cout << "到达文件末尾会触发 io.eof() 与 io.fail()" << endl;
    input.close();
}


int main()
{   
    const char* filename{"ReadFile.cpp"};
    demo(filename);
    vector<string> vector_1;
    readlines_while(filename, vector_1);
}