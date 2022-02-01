#include "ReadJson.h"
#include <stdio.h>

// 设置缩进
static void SetIndent(char* s, int deep)
{   
    int j{0};
    for (int i=0; i<deep; ++i, j++)
    {
        s[j] = ' ';
    }
    s[j] = 0;
}

JsonUnitType::JsonUnitType(const JsonUnitType& unit)
{   
    _type = unit._type;
    switch (_type)
    {
    case JsonUnitTypeType::DICT:
        _pDict = new std::map<std::string, JsonUnitType>{};
        if (unit._pDict != nullptr)
            *_pDict = *(unit._pDict); 
        break;
    case JsonUnitTypeType::LIST:
        _pList = new std::vector<JsonUnitType>{};
        if (unit._pList != nullptr)
            *_pList = *(unit._pList); 
        break;
    case JsonUnitTypeType::STRING:
        _pString = new std::string{};
        if (unit._pString != nullptr);
            *_pString = *(unit._pString); 
        break;
    case JsonUnitTypeType::INT:
        _int = unit._int;
        break;
    case JsonUnitTypeType::DOUBLE:
        _double = unit._double;
        break;
    case JsonUnitTypeType::BOOL:
        _bool = unit._bool;
        break;
    default:
        ;
    }
}

JsonUnitType::JsonUnitType(int i)
{
    _type = JsonUnitTypeType::INT;
    _int = i;
}

JsonUnitType::JsonUnitType(double d)
{
    _type = JsonUnitTypeType::DOUBLE;
    _double = d;
}

JsonUnitType::JsonUnitType(bool b)
{
    _type = JsonUnitTypeType::BOOL;
    _bool = b;
}

JsonUnitType::JsonUnitType(const char * str)
{   
    _type = JsonUnitTypeType::STRING;
    if (str != nullptr)
        _pString = new std::string{str};
    else
        _pString = new std::string{""};
}

JsonUnitType::JsonUnitType(const std::string &s)
{   
    _type = JsonUnitTypeType::STRING;
    _pString = new std::string{s};
}

JsonUnitType::JsonUnitType(const std::vector<JsonUnitType> &vec)
{   

    _type = JsonUnitTypeType::LIST;
    _pList = new std::vector<JsonUnitType>;
    *_pList = vec;
    printf("create list\n");
}

JsonUnitType::JsonUnitType(const std::map<std::string, JsonUnitType>& dict)
{   
    printf("create dict\n");
    _type = JsonUnitTypeType::DICT;
    _pDict = new std::map<std::string, JsonUnitType>;
    *_pDict = dict;
    printf("create dict\n");
}

JsonUnitType::~JsonUnitType()
{
    switch (_type)
    {
    case JsonUnitTypeType::DICT:
        _pDict->clear();
        delete _pDict;
        _pDict = nullptr;
        break;
    case JsonUnitTypeType::LIST:
        _pList->clear();
        delete _pList;
        _pList = nullptr;
        break;
    case JsonUnitTypeType::STRING:
        _pString->clear();
        delete _pString;
        _pString = nullptr;
        break;
    default:
        ;
    }
}
// 打印json 单元
extern void ShowJsonUnit(const JsonUnitType& unit, int deep);

// 打印json的字典结构
static void ShowJsonDict(const JsonDictType &config, int deep)
{   
    // 设置缩进
    char indent_str[128];
    SetIndent(indent_str, deep);
    // 计数
    unsigned count{0};
    printf("{");
    for (const std::pair<const std::string, JsonUnitType> &iter: config)
    {   
        if (count != 0)
            printf(",\n%s ", indent_str);
        const std::string &key = iter.first;
        int bias = printf("\"%s\": ", key.c_str());
        const JsonUnitType& unit = iter.second;
        ShowJsonUnit(unit, deep + bias);
        ++count;
    }
    printf("}");
}

// 打印json的列表结构
void ShowJsonList(const JsonListType &list, int deep)
{   
    // 设置缩进
    char indent_str[128];
    SetIndent(indent_str, deep);
    printf("[");
    unsigned count{0};
    for (; count < GetJsonListSize(list); ++count)
    {   
        int bias = 0;
        if (count != 0)
            bias = printf(",\n%s  ", indent_str);
        ShowJsonUnit(list[count], deep + bias);
    }
    printf("]");
}

// 打印json的unit
void ShowJsonUnit(const JsonUnitType& unit, int deep)
{   
    char bool_arr[2][8]{"false", "true"};
    switch (unit._type)
    {
    case JsonUnitTypeType::DICT:
        ShowJsonDict(*(unit._pDict), deep); break;
    case JsonUnitTypeType::LIST:
        ShowJsonList(*(unit._pList), deep); break;
    case JsonUnitTypeType::STRING:
        printf("\"%s\"", unit._pString->c_str()); break;
    case JsonUnitTypeType::DOUBLE:
        printf("%.4lf", unit._double); break;
    case JsonUnitTypeType::INT:
        printf("%d", unit._int); break;
    case JsonUnitTypeType::BOOL:
        printf("%s", bool_arr[unit._bool]); break;
    default:
        printf("Unknown Type");
    }
}

// 显示已读取的配置
void ShowJson(const JsonDictType &config)
{   
    // 缩进深度
    int deep{0};
    ShowJsonDict(config, deep);
    printf("\n");
}

// 读取配置文件
const JsonDictType ReadJson(const char* filename)
{
    JsonDictType json;
    return json;
}

// 获取键值为 key 的子章节 无此章节返回空值
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
const JsonDictType& GetDictFromJsonDict(const JsonDictType& dict, const std::string & key)
{
    static JsonDictType emptyDict{};
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return emptyDict;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::DICT || iter->second._pDict == nullptr)
        return emptyDict;
    else
        return *(iter->second._pDict);
}
// 获取键值为 key 的子列表 无此列表章节返回空值
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
const JsonListType& GetListFromJsonDict(const JsonDictType& dict, const std::string & key)
{
    static JsonListType emptyList{};
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return emptyList;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::LIST || iter->second._pList == nullptr)
        return emptyList;
    else
        return *(iter->second._pList);
}

// 获取指定键值对应的字符串 无此键值返回 默认字符串
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const std::string & default_value = "" 默认值
const std::string GetStringFromJsonDict(const JsonDictType& dict, const std::string & key, const std::string default_value)
{   
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return default_value;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::STRING || iter->second._pString == nullptr)
        return default_value;
    else
        return *(iter->second._pString);
}

// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const int default = 0 默认值
int GetIntFromJsonDict(const JsonDictType& dict, const std::string & key, int default_value)
{
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return default_value;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::INT)
        return default_value;
    else
        return iter->second._int;
}
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const double default_value = 0.0 默认值
double GetDoubleFromJsonDict(const JsonDictType& dict, const std::string & key, double default_value)
{
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return default_value;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::DOUBLE)
        return default_value;
    else
        return iter->second._double;
}
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonDictType& dict Json字典类型
// const std::string & key 键值
// const bool default_value = false 默认值
bool GetStringFromJsonDict(const JsonDictType& dict, const std::string & key, bool default_value)
{
    // 查找
    JsonDictType::const_iterator iter = dict.find(key);
    if (iter == dict.end())
        return default_value;
    // 类型验证 空指针验证
    else if (iter->second._type == JsonUnitTypeType::BOOL)
        return default_value;
    else
        return iter->second._bool;
}


// 获取第idx个子章节 无此章节返回空值
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
const JsonDictType& GetDictFromJsonList(const JsonListType& list, unsigned idx)
{
    static JsonDictType emptyDict{};
    if (idx >= list.size())
        return emptyDict;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::LIST || list[idx]._pDict == nullptr)
        return emptyDict;
    else
        return *(list[idx]._pDict);
}
// 获取第idx个列表 无此列表章节返回空值
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
const JsonListType& GetListFromJsonList(const JsonListType& list, unsigned idx)
{
    static JsonListType emptyList{};
    if (idx >= list.size())
        return emptyList;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::LIST || list[idx]._pList == nullptr)
        return emptyList;
    else
        return *(list[idx]._pList);
}

// 获取 列表对象容量大小
unsigned GetJsonListSize(const JsonListType& list)
{
    return list.size();
}

// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const std::string & default_value = "" 默认值
const std::string GetStringFromJsonList(const JsonListType& list, unsigned idx, const std::string default_value)
{
    if (idx >= list.size())
        return default_value;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::STRING || list[idx]._pList == nullptr)
        return default_value;
    else
        return *(list[idx]._pString);
}

// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const int default = 0 默认值
int GetIntFromJsonList(const JsonListType& list, unsigned idx, const int default_value)
{
    if (idx >= list.size())
        return default_value;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::INT)
        return default_value;
    else
        return list[idx]._int;
}

// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const double default_value = 0.0 默认值
double GetDoubleFromJsonList(const JsonListType& list, unsigned idx, const double default_value)
{
    if (idx >= list.size())
        return default_value;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::DOUBLE)
        return default_value;
    else
        return list[idx]._double;
}
// 获取指定键值对应的字符串 无此键值返回 默认字符串default
// const JsonListType& list Json列表类型
// unsigned idx 第几个元素
// const bool default_value = false 默认值
bool GetStringFromJsonList(const JsonListType& list, unsigned idx, const bool default_value)
{
    if (idx >= list.size())
        return default_value;
    // 类型验证 空指针验证
    else if (list[idx]._type == JsonUnitTypeType::BOOL)
        return default_value;
    else
        return list[idx]._bool;
}

// 从列表对象JsonList中获取字符串列表 
// const JsonListType& list Json列表类型
std::vector<std::string> GetVectorStringFromJsonList(const JsonListType& list)
{
    std::vector<std::string> vec{};
    return vec;
}
// 从列表对象JsonList中获取整数列表 
// const JsonListType& list Json列表类型
std::vector<int> GetVectorIntFromJsonList(const JsonListType& list)
{
    std::vector<int> vec{};
    return vec;
}

// 从列表对象JsonList中获取浮点数列表 
// const JsonListType& list Json列表类型
// std::vector<double> &vec 待赋值数组
std::vector<double> GetVectorDoubleFromJsonList(const JsonListType& list)
{
    std::vector<double> vec{};
    return vec;
}

// 从列表对象JsonList中获取布尔列表 
// const JsonListType& list Json列表类型
std::vector<bool> GetVectorBoolFromJsonList(const JsonListType& list)
{
    std::vector<bool> vec{};
    return vec;
}