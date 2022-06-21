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


#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::duration;                    // 时间段
using std::chrono::system_clock;                // 系统时间
using std::chrono::duration_cast;               // 时间类型转换
#include "Code2Pos1.h"
#include "Code2Pos2.h"
#include "Code2Pos3.h"

/*
g++ -std=c++11 Code2Pos1.h Code2Pos2.h Code2Pos3.h Code2Pos1.cpp Code2Pos2.cpp Code2Pos3.cpp codemap.cpp -o codemap.out
*/
steady_clock::time_point GetTime() 
{
    steady_clock::time_point time_ed = steady_clock::now();
} 

int64_t DiffTime(const steady_clock::time_point &time_st, const steady_clock::time_point &time_ed)
{
    steady_clock::duration d1 = time_ed - time_st;
    return d1.count();
}

void test_1(vector<string>& code_list, map<string, int> &code_map)
{
    for (string code: code_list)
    {
        map<string, int>::iterator iter = code_map.find(code);
    }
}

void InitialCodeMap(vector<string>& code_list, map<string, int> &code_map, int limit)
{   
    int count{0};
    for (string code: code_list)
    {
        map<string, int>::iterator iter = code_map.find(code);
        if (iter == code_map.end())
        {
            code_map[code] = 1;
        }
        if (++count > limit)
            break;
    }
    printf("load %d data code_map size:%lu\n", count, code_map.size());
}


void test_2(vector<string>& code_list)
{
    for (string code: code_list)
        int pos = Code2Pos1::FindCode(code.c_str());
}

void test_3(vector<string>& code_list)
{
    for (string code: code_list)
        int pos = Code2Pos2::FindCode(code.c_str());
}

void test_4(vector<string>& code_list)
{
    for (string code: code_list)
        int pos = Code2Pos3::FindCode(code.c_str());
}

vector<string> ReadCodelist(int limit)
{   
    steady_clock::time_point time_st = GetTime();
    ifstream file_codelist("codelist.txt");
    const size_t line_size = 1024;
    char line_c[line_size];
    int count{0};
    vector<string> code_list;
    istringstream line_in;
    if (file_codelist.bad())
        printf("error in open file codelist");
    if (file_codelist.fail())
        printf("fail in open file codelist");

    file_codelist.getline(line_c, line_size);
    while((!file_codelist.eof())&&(!file_codelist.fail()) && (++count <= limit))
    {
        string code{line_c, line_c + 6};
        if (code.size() == 6)
        {   
            code_list.push_back(code);
        }
        file_codelist.getline(line_c, line_size);
    }
    steady_clock::time_point time_ed = GetTime();
    double useTime =DiffTime(time_st, time_ed) / 1000000000.0;
    printf("code list size:%ld used:%.3lfs\n", code_list.size(), useTime);
    return code_list;
}

int main()
{   
    int limit{13000 * 10000};
    vector<string> code_list = ReadCodelist(limit);
    double size = code_list.size();
    map<string, int> code_map{};
    steady_clock::time_point time_st, time_ed;
    InitialCodeMap(code_list, code_map, 2 * 10000);
    time_st = GetTime();
    test_1(code_list, code_map);
    time_ed = GetTime();
    printf("test map       avg:%.4lfns used:%.3lfs\n", DiffTime(time_st, time_ed) / size, DiffTime(time_st, time_ed) / 1000000000.0);

    Code2Pos1::InitialSearchTable();
    time_st = GetTime();
    test_2(code_list);
    time_ed = GetTime();
    printf("test code arr1 avg:%.4lfns used:%.3lfs\n", DiffTime(time_st, time_ed) / size, DiffTime(time_st, time_ed) / 1000000000.0);
    Code2Pos1::ReleaseSearchTable();

    Code2Pos2::InitialSearchTable();
    time_st = GetTime();
    test_3(code_list);
    time_ed = GetTime();
    printf("test code arr2 avg:%.4lfns used:%.3lfs\n", DiffTime(time_st, time_ed) / size, DiffTime(time_st, time_ed) / 1000000000.0);
    Code2Pos2::ReleaseSearchTable();
    
    Code2Pos3::InitialSearchTable();
    time_st = GetTime();
    test_4(code_list);
    time_ed = GetTime();
    printf("test code arr3 avg:%.4lfns used:%.3lfs\n",  DiffTime(time_st, time_ed) / size, DiffTime(time_st, time_ed) / 1000000000.0);
    Code2Pos3::ReleaseSearchTable();
    return 0;
}