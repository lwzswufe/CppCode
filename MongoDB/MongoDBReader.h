#include <cstdlib>
#include <iostream>
#include <string>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/types.hpp>

#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/options/client.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using Value = bsoncxx::document::value;
using ConditionList = bsoncxx::v_noabi::builder::basic::document;           // 条件列表 可使用append方法增加条件Condition
using Cursor = mongocxx::v_noabi::cursor;                                   // 数据表游标

 
 template <typename T>
using Condition = std::tuple<const char*, T&&>;                             // 筛选条件
#define Equal(k, v) (kvp(k, make_document(kvp("$eq", v))))                  // 等于    doc[k] == v
#define NotEqual(k, v) (kvp(k, make_document(kvp("$ne", v))))               // 不等于  doc[k] != v
#define GraterThan(k, v) (kvp(k, make_document(kvp("$gt", v))))             // 大于    doc[k] >  v
#define LessThan(k, v) (kvp(k, make_document(kvp("$lt", v))))               // 小于    doc[k] <  v
#define GraterThanOrEqual(k, v) (kvp(k, make_document(kvp("$gte", v))))     // 大于等于 doc[k] >= v
#define LessThanOrEqual(k, v) (kvp(k, make_document(kvp("$lte", v))))       // 小于等于 doc[k] <= v
struct Data
{
    int Code;
    char Name[32];
};

class MongoDBReader
{
public:
    // 登录
    // const char* ip IP地址 如 127.0.0.1
    // const char* port 端口号 如 27017
    // const char* user 用户名 可为空
    // const char* pwd 密码 可为空
    void Login(const char* ip, const char* port, const char* user, const char* pwd);
    // 登出
    void Logout();
    // 查询所有数据
    void QueryAll(std::vector<Data> &DataVec);
    // 查询指定范围的数据
    void QueryBetween(std::vector<Data> &DataVec, int min_code, int max_code);
    // 选择某一个数据库
    void SelectCollection(const char* basename, const char* collectionname);
    // 输出条件列表
    static void PrintConditionList(const ConditionList& condlist);
protected:
    // 从查询结果中解析数据
    static void ParseDataFromCursor(std::vector<Data> &DataVec, Cursor &cursor);
    // 驱动实例
    mongocxx::instance _Instance;
    // 连接句柄
    mongocxx::client _Client;
    // 数据表
    mongocxx::collection _Collection;
    // 当前连接数据库名
    char _BaseName[128] {0};
    // 当前连接数据表名
    char _CollectionName[128] {0};
    // 当前连接用户名
    char _UserName[128] {0};
    // 当前服务器地址
    char _Url[128] {0};
};