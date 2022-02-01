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


// Json单元的数据类型
enum class JsonUnitTypeType
{
    UNKNOWN = 0,    // 未定义
    DICT    = 1,    // 字典
    LIST    = 2,    // 列表
    STRING  = 3,    // 值--字符串
    DOUBLE  = 4,    // 值--浮点数
    INT     = 5,    // 值--整数
    BOOL    = 6     // 值--布尔变量
};

// Json单元类型
struct JsonUnitType
{   
public:
    union
    {
        std::map<std::string, JsonUnitType> *_pDict;        // 字典
        std::vector<JsonUnitType> *_pList;                  // 列表
        std::string *_pString;                              // 字符串
        double _double;                                     // 浮点数
        int _int;                                           // 整数
        bool _bool;                                         // 布尔变量
    };
    JsonUnitType();
    ~JsonUnitType();
    JsonUnitType(const JsonUnitType& unit);
    JsonUnitType(int i);
    JsonUnitType(double d);
    JsonUnitType(bool b);
    JsonUnitType(const std::string &s);
    JsonUnitType(const char* s);
    JsonUnitType(const std::vector<JsonUnitType> &vec);
    JsonUnitType(const std::map<std::string, JsonUnitType>& dict);
    // JsonUnitType& operator=(const JsonUnitType& unit);
    JsonUnitTypeType _type;      // json 数据类型

};
// Json字典类型
typedef std::map<std::string, JsonUnitType> JsonDictType;
// Json列表类型
typedef std::vector<JsonUnitType> JsonListType;


// 显示已读取的配置
void ShowJson(const JsonDictType &config);
// 读取配置文件
const JsonDictType ReadJson(const char* filename);   

void ShowJsonList(const JsonListType &list, int deep);

// 获取键值为 key 的子章节 无此章节返回空值
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
const JsonDictType& GetDictFromJsonDict(const JsonDictType& dict, const std::string & key);
// 获取键值为 key 的子列表 无此列表章节返回空值
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
const JsonListType& GetListFromJsonDict(const JsonDictType& dict, const std::string & key);

// 获取指定键值对应的字符串 无此键值返回 默认字符串
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const std::string & default_value = "" 默认值
const std::string GetStringFromJsonDict(const JsonDictType& dict, const std::string & key, const std::string default_value = "");
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const int default = 0 默认值
int GetIntFromJsonDict(const JsonDictType& dict, const std::string & key, int default_value = 0);
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const double default_value = 0.0 默认值
double GetDoubleFromJsonDict(const JsonDictType& dict, const std::string & key, double default_value = 0.0);
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const bool default_value = false 默认值
bool GetStringFromJsonDict(const JsonDictType& dict, const std::string & key, bool default_value = false);


// 获取第idx个子章节 无此章节返回空值
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
const JsonDictType& GetDictFromJsonList(const JsonListType& list, unsigned idx);
// 获取第idx个列表 无此列表章节返回空值
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
const JsonListType& GetListFromJsonList(const JsonListType& list, unsigned idx);
// 获取 列表对象容量大小
unsigned GetJsonListSize(const JsonListType& list);

// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const std::string & default_value = "" 默认值
const std::string GetStringFromJsonList(const JsonListType& list, unsigned idx, const std::string & = "");
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const int default = 0 默认值
int GetIntFromJsonList(const JsonListType& list, unsigned idx, const int = 0);
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const double default_value = 0.0 默认值
double GetDoubleFromJsonList(const JsonListType& list, unsigned idx, const double = 0.0);
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const bool default_value = false 默认值
bool GetStringFromJsonList(const JsonListType& list, unsigned idx, const bool = false);

// 从列表对象JsonList中获取字符串列表 
// const JsonListType& list Json列表类型
std::vector<std::string> GetVectorStringFromJsonList(const JsonListType& list);
// 从列表对象JsonList中获取整数列表 
// const JsonListType& list Json列表类型
std::vector<int> GetVectorIntFromJsonList(const JsonListType& list);
// 从列表对象JsonList中获取浮点数列表 
// const JsonListType& list Json列表类型
// std::vector<double> &vec 待赋值数组
std::vector<double> GetVectorDoubleFromJsonList(const JsonListType& list);
// 从列表对象JsonList中获取布尔列表 
// const JsonListType& list Json列表类型
std::vector<bool> GetVectorBoolFromJsonList(const JsonListType& list);
