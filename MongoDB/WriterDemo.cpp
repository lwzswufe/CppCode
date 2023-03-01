#include "MongoDBWriter.h"

/*
c++ --std=c++11 MongoDBReader.h MongoDBReader.cpp MongoDBWriter.h MongoDBWriter.cpp WriterDemo.cpp -o WriterDemo.o \
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
    MongoDBWriter writer;
    if (argc < 5)
        writer.Login(argv[1], argv[2], nullptr, nullptr);
    else 
        writer.Login(argv[3], argv[4], argv[1], argv[2]);
    // 选择数据库 数据表
    writer.SelectCollection("testdb", "testco");
    // 清除所有数据
    writer.Clear();  
    std::vector<std::string>name_vec {"alpha", "beta", "gamma", "Delta"};
    // 一次插入一条数据
    for (unsigned i=0; i<name_vec.size(); ++i)
    {   
        Data data{i};
        strncpy(data.Name, name_vec[i].c_str(), 32);
        writer.Insert_One(&data);
    }
    // 一次插入多条数据
    Data arr[4];
    for (unsigned i=0; i<name_vec.size(); ++i)
    {   
        arr[i].Code = i + 4;
        strncpy(arr[i].Name, name_vec[i].c_str(), 32);
    }
    writer.Insert_Many(arr, 4);
    // 更新
    Data data{3, "Cindy"};
    writer.Update_One(&data);
    // 数组
    std::vector<int> vec{1,3,5,7,9};
    writer.Insert_List(&data, vec);
    // 登出
    writer.Logout();
    return 0;
}