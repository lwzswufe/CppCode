#include "MongoDBReader.h"

class MongoDBWriter : public MongoDBReader
{  
public: 
    // 插入数据
    void Insert_One(const Data* data);
    // 插入多条数据
    void Insert_Many(const Data* data, int num);
    // 更新一条数据
    void Update_One(const Data* data);
    // 清空数据表
    void Clear();
};