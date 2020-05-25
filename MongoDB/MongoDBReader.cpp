#include "MongoDBReader.h"

void MongoDBReader::Login(const char* ip, const char* port, const char* user, const char* pwd)
{   
    // 生成统一资源标识符URI的字符串uri_s
    char uri_s[256];
    if (user == nullptr)
    {
        sprintf(uri_s, "mongodb://%s:%s", ip, port);
    }
    else
    {
        sprintf(uri_s, "mongodb://%s:%s@%s:%s", ip, port, user, pwd);
    }
    // 获取统一资源标识符URI
    const mongocxx::v_noabi::uri uri = mongocxx::uri{uri_s};
    // 连接数据库服务器
    _Client = mongocxx::client{uri};
    // 尝试获取数据库名称 来判断是否连接成功
    try
    {
        std::vector<std::string> db_name_vec = _Client.list_database_names();
    }
    catch(const std::exception& xcp)
    {
        printf("Login %s:%s failed:%s\n", ip, port, xcp.what());
    }
    printf("Login %s:%s successful\n", ip, port);
}

void MongoDBReader::Logout()
{
    _Client.~client();
    printf("Logout successful\n");
}

void MongoDBReader::QueryAll(const char* basename, const char* collectionname)
// Query for all the documents in a collection.
{   
    mongocxx::v_noabi::database db = _Client[basename];
    // @begin: cpp-query-all
    mongocxx::v_noabi::cursor cursor = db[collectionname].find({});
    size_t count = 0;
    for (auto&& doc : cursor) 
    {   
        for (auto&& element: doc)
        {
            std::cout << element.key() << ":";
            if (element.type() == bsoncxx::type::k_oid)
            {
                std::cout << element.get_oid().value.to_string();
            }
            else if (element.type() == bsoncxx::type::k_utf8)
            {
                std::cout << element.get_utf8().value;
            }
            std::cout << ", ";
        }
        std::cout << std::endl;
        count++;
    }
    printf("%s[%s] total:%ld data\n", basename, collectionname, count);
    // @end: cpp-query-all
}