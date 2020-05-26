#include "MongoDBWriter.h"
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;


void MongoDBWriter::Insert_One(Data* data)
{   
    static int count{0};
    if (count % 2 == 0)
    {   // 插入方法1
        bsoncxx::builder::stream::document document{};
        document // << "_id"  << count
                 << "Name" << data->Name
                 << "Code" << data->Code;
        std::cout << bsoncxx::to_json(document) << std::endl;
        _Collection.insert_one(document.view());
    }
    else
    {   // 插入方法2
        bsoncxx::document::value doc = make_document(
        //    kvp("_id",  count),
            kvp("Name", data->Name),
            kvp("Code", data->Code));
        std::cout << bsoncxx::to_json(doc.view()) << std::endl;
        // 这里必须使用std::move  使用后 原有doc内容会失效
        auto res = _Collection.insert_one(std::move(doc));
        std::cout << "InsertNum:" << res.value().result().inserted_count() << std::endl;
    }
    ++count;
}

void MongoDBWriter::Insert_Many(Data* data, int num)
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

void MongoDBWriter::Clear()
{
    auto res = _Collection.delete_many({});
    printf("Clear %s[%s] All Data %d\n", _BaseName, _CollectionName, res.value().deleted_count());
}