#include "MongoDBReader.h"

/*
c++ --std=c++11 MongoDBReader.h MongoDBReader.cpp ReaderDemo.cpp -o ReaderDemo.o \
   -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
  -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
  -L/usr/local/lib -lmongocxx -lbsoncxx 
*/

int main(int argc, char* argv[])
{
    if (argc < 2)
    {   
        printf("args is not enough\n");
        return -1;
    }
    MongoDBReader reader;
    if (argc < 5)
        reader.Login(argv[1], argv[2], nullptr, nullptr);
    else 
        reader.Login(argv[1], argv[2], argv[3], argv[4]);
    // 选择数据库 数据表
    reader.SelectCollection("testdb", "testco");  
    std::vector<Data> DataVec;  
    reader.QueryAll(DataVec);
    for (Data data:DataVec)
    {
        printf("Code:%d Name:%s\n", data.Code, data.Name);
    }
    DataVec.clear();
    reader.QueryBetween(DataVec, 3, 5);
    for (Data data:DataVec)
    {
        printf("Code:%d Name:%s\n", data.Code, data.Name);
    }
    // 登出
    reader.Logout();
    //
    std::cout<< "over" << std::endl;
    return 0;
}