#include "MongoDBReader.h"

void MongoDBReader::Login(const char* ip, const char* port, const char* user, const char* pwd)
{   
    // 生成统一资源标识符URI的字符串uri_s
    char uri_s[256];
    if (user == nullptr)
    {   
        sprintf(_UserName, "nullptr");
        sprintf(uri_s, "mongodb://%s:%s", ip, port);
    }
    else
    {   
        // 记录用户名
        strncpy(_UserName, user, 128);
        sprintf(uri_s, "mongodb://%s:%s@%s:%s", ip, port, user, pwd);
    }
    // 记录服务器地址
    sprintf(_Url, "%s:%s", ip, port);
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
    printf("%s user:%s Logout successful\n", _Url, _UserName);
}

void MongoDBReader::SelectCollection(const char* basename, const char* collectionname)
{
    mongocxx::v_noabi::database db = _Client[basename];
    strncpy(_BaseName, basename, 128);
    _Collection = db[collectionname];
    strncpy(_CollectionName, collectionname, 128);
    printf("Connect db:%s table:%s\n", _BaseName, _CollectionName);
}

void MongoDBReader::QueryAll(std::vector<Data> &DataVec)
// Query for all the documents in a collection.
{   
    mongocxx::v_noabi::cursor cursor = _Collection.find({});
    size_t count = 0;
    for (auto&& doc : cursor) 
    {   
        // 获取数据
        Data data;
        data.Code = doc["Code"].get_int32();
        strncpy(data.Name, doc["Name"].get_utf8().value.to_string().c_str(), 32);
        DataVec.push_back(data);
        // 输出信息
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
            else if (element.type() == bsoncxx::type::k_int32)
            {
                std::cout << element.get_int32().value;
            }
            std::cout << ", ";
        }
        std::cout << std::endl;
        count++;
    }
    printf("%s[%s] total:%ld data\n", _BaseName, _CollectionName, count);
    // @end: cpp-query-all
}