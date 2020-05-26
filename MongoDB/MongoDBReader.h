#include <cstdlib>
#include <iostream>
#include <string>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <mongocxx/options/client.hpp>
#include <mongocxx/uri.hpp>


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
    // 选择某一个数据库
    void SelectCollection(const char* basename, const char* collectionname);
protected:
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