#pragma once
#include <cstdio>
#include <map>
#include <fstream>
#include <exception>
#include <string.h>
#include <string>
#include <vector>
#include <exception>
using std::runtime_error;
typedef std::map<std::string, std::map<std::string, std::string>> IniType;
typedef std::map<std::string, std::string> IniSectionType;

// 显示已读取的配置
void ShowIni(IniType config);
// 读取配置文件
IniType ReadIni(const char* filename);                         
// 从一个章节中读取整数
int GetIntFromKey(IniSectionType &section, std::string key);
// 从一个章节中读取浮点数
double GetDoubleFromKey(IniSectionType &section, std::string key);
// 从一个章节中读取浮点数组
std::vector<double> GetVectorDoubleFromKey(IniSectionType &section, std::string key);
