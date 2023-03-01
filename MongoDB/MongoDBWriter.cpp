#include "MongoDBWriter.h"
using bsoncxx::builder::basic::sub_array;


void MongoDBWriter::Insert_One(const Data* data)
{   
    static int count{0};
    // 获取当前时间
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now() + TimeDifference;
    // 转换为bson时间
    BsonDate datetime = BsonDate(today);
    if (count % 2 == 0)
    {   // 插入方法1
        bsoncxx::builder::stream::document document{};
        document << "_id"  << count
                 << "Name" << data->Name
                 << "Code" << data->Code
                 << "Time" << datetime;
        std::cout << bsoncxx::to_json(document) << std::endl;
        _Collection.insert_one(document.view());
    }
    else
    {   // 插入方法2
        bsoncxx::document::value doc = make_document(
            kvp("_id",  count),
            kvp("Name", data->Name),
            kvp("Code", data->Code), 
            kvp("Time", datetime));
        std::cout << bsoncxx::to_json(doc.view()) << std::endl;
        // 这里必须使用std::move  使用后 原有doc内容会失效
        auto res = _Collection.insert_one(std::move(doc));
        std::cout << "InsertNum:" << res.value().result().inserted_count() << std::endl;
    }
    ++count;
}

void MongoDBWriter::Insert_Many(const Data* data, int num)
{   
    std::vector<bsoncxx::document::value> DocVec;
    // 获取当前时间
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now() + TimeDifference;
    // 转换为bson时间
    BsonDate datetime = BsonDate(today);
    for (int i=0; i<num; ++i)
    {   
        bsoncxx::document::value doc = make_document(
                                        // kvp("_id",  oid),
                                        kvp("Name", data[i].Name),
                                        kvp("Code", data[i].Code),
                                        kvp("Time", datetime));
        DocVec.push_back(doc);
    }
    auto res = _Collection.insert_many(DocVec);
    printf("%s[%s] Insert %d Data\n", _BaseName, _CollectionName, res.value().inserted_count());
}

// 插入数据
void MongoDBWriter::Insert_List(const Data* data, std::vector<int> vec)
{
    bsoncxx::document::value doc = make_document(
            kvp("_id",  100),
            kvp("Name", data->Name),
            kvp("Code", data->Code), 
            kvp("Arr", [&vec](sub_array child) 
                        {
                            for (const auto& element : vec) {
                                child.append(element);
                            }
                        })
                );
    // std::cout << bsoncxx::to_json(doc.view()) << std::endl;
    auto res = _Collection.insert_one(doc.view());
    std::cout << "InsertNum:" << res.value().result().inserted_count() << std::endl;
}

void MongoDBWriter::Update_One(const Data* data)
{
    auto res = _Collection.update_one(make_document(kvp("Code", data->Code)),
                                      make_document(kvp("$set", make_document(kvp("Name", data->Name)))));
    printf("%s[%s] Update %d Data\n", _BaseName, _CollectionName, res.value().modified_count());
}

// void MongoDBWriter::Update_One(const Data* data)
// {
//     _Collection.update_one(make_document(kvp("$", "3")),
//                            make_document(kvp("$set", make_document(kvp("address.street", "East 31st Street"));
// }


void MongoDBWriter::Clear()
{
    auto res = _Collection.delete_many({});
    printf("Clear %s[%s] All Data %d\n", _BaseName, _CollectionName, res.value().deleted_count());
}