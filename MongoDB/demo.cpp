#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

/*
g++ demo.cpp -I "/usr/local/include/bsoncxx/v_noabi" -I "/usr/local/include/mongocxx/v_noabi" -L "/usr/local/lib" -lbsoncxx -lmongocxx -o demo.o
c++ --std=c++11 demo.cpp $(pkg-config --cflags --libs libmongocxx)
c++ --std=c++11 demo.cpp -o demo.o \
   -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
  -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
  -L/usr/local/lib -lmongocxx -lbsoncxx 
c++ --std=c++11 demo.cpp -o demo.out \
    -DMONGOCXX_STATIC -DBSONCXX_STATIC -DMONGOC_STATIC -DBSON_STATIC \
    -I/usr/local/include/libmongoc-1.0 \
    -I/usr/local/include/libbson-1.0 \
    -I/usr/local/include/mongocxx/v_noabi \
    -I/usr/local/include/bsoncxx/v_noabi \
    -L/usr/local/lib -lmongocxx-static -lbsoncxx-static
    -lmongoc-static-1.0 -lsasl2 -lssl -lcrypto -lbson-static-1.0 -lm -lpthread
*/

int main(int, char**) {
    mongocxx::instance inst{};
    std::cout << "get instance" << std::endl;
    mongocxx::client conn{mongocxx::uri{"mongodb://127.0.0.1:27017"}};
    std::cout << "create conn" << std::endl;
    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}