#include "MongoDBReader.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/types.hpp>


class MongoDBWriter : public MongoDBReader
{  
public: 
    // 插入数据
    void Insert_One(Data* data);
    // 插入多条数据
    void Insert_Many(Data* data, int num);
    // 清空数据表
    void Clear();
};