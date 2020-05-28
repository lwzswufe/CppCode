#include "MongoDBWriter.h"


void MongoDBWriter::Insert_One(const Data* data)
{   
    static int count{0};
    if (count % 2 == 0)
    {   // 插入方法1
        bsoncxx::builder::stream::document document{};
        document // << "_id"  << count
                 << "Name" << data->Name
                 << "Code" << data->Code
                 << "Time" << "2020-04-10 14:55:23";
        std::cout << bsoncxx::to_json(document) << std::endl;
        _Collection.insert_one(document.view());
    }
    else
    {   // 插入方法2
        bsoncxx::document::value doc = make_document(
        //    kvp("_id",  count),
            kvp("Name", data->Name),
            kvp("Code", data->Code), 
            kvp("Time", "2020-04-10 14:55:23"));
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
    for (int i=0; i<num; ++i)
    {
        bsoncxx::document::value doc = make_document(
                                        // kvp("_id",  data[i].Code),
                                        kvp("Name", data[i].Name),
                                        kvp("Code", data[i].Code));
        DocVec.push_back(doc);
    }
    auto res = _Collection.insert_many(DocVec);
    printf("%s[%s] Insert %d Data\n", _BaseName, _CollectionName, res.value().inserted_count());
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