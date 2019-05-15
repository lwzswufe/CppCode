#include <stdio.h>
#include <string>
#include <stdlib.h>
#define CODEARRSIZE 7000

int code2pos(const char * code)
{    // 证券代码字符串转化为数组坐标 效率是map<string，int>的5倍
    int head = (code[0] - 48) * 10 + (code[2] - 48);
    int bias, pos;
    switch (head)
    {
    case 0:                                                     // 000XXX
        bias = 0;   break;
    case 1:                                                     // 001XXX
        bias = 1000;break;
    case 2:                                                     // 002XXX
        bias = 2000;break;
    case 30:                                                    // 300XXX
        bias = 3000;break;
    case 60:                                                    // 600XXX 
        bias = 4000;break;
    case 61:                                                    // 601XXX
        bias = 5000;break;
    case 63:                                                    // 603XXX
        bias = 6000;break;
    default:
        return 0;
    }
    // pos = atoi(code) - bias;
    pos = bias + (code[3] - 48) * 100 + (code[4] - 48) * 10 + (code[5] - 48);
    if (pos < 0 || pos > CODEARRSIZE)
        return 0;
    else
        return pos;
}

#include <time.h> 
#include <sys/time.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;

double getTime() 
{   // 获取精确到毫秒的时间
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
       
    gettimeofday(&tv, &tz);
       
    p = localtime(&tv.tv_sec); 
    return  p->tm_hour*3600+p->tm_min * 60 + p->tm_sec + tv.tv_usec / 1000000.0; 
} 

void test_1(vector<string> code_list, int * arr)
{
    for (string code: code_list)
        arr[code2pos(code.c_str())];
}

void test_2(vector<string> code_list, map<string, int> &code_map)
{
    for (string code: code_list)
        code_map[code];
}

vector<string> read_codelist()
{   
    ifstream file_codelist("Codelist.txt");
    const size_t line_size = 1024;
    char line_c[line_size];
    vector<string> code_list;
    istringstream line_in;
    if (file_codelist.bad())
        printf("error in open file codelist");
    if (file_codelist.fail())
        printf("fail in open file codelist");

    file_codelist.getline(line_c, line_size);
    while((!file_codelist.eof())&&(!file_codelist.fail()))
    {
        string code{line_c, line_c + 6};
        if (code.size() == 6 && (code[0] == '0' || code[0] == '3' || code[0] == '6'))
        {   
            code_list.push_back(code);
        }
        else if(code != "codeli")
            ;
        file_codelist.getline(line_c, line_size);
    }
    printf("code list size:%ld\n", code_list.size());
    return code_list;
}

int main()
{   
    int arr[CODEARRSIZE];
    int cycle_times = 1000, map_size=500;
    vector<string> code_list = read_codelist();
    map<string, int> code_map;
    double st_time;
    int i = 0, size = code_list.size();
    while (code_map.size() < map_size)
    {   
        i+=47;
        if (i >= size)
            i -= size;
        code_map[code_list[i]] = 0;
    }
    st_time = getTime();
    for (int i=0; i<cycle_times; i++)
        test_1(code_list, arr);
    printf("test1 used:%.3lfs\n", getTime() - st_time);
    st_time = getTime();
    for (int i=0; i<cycle_times; i++)
        test_2(code_list, code_map);
    printf("test2 used:%.3lfs\n", getTime() - st_time);
    return 0;
}