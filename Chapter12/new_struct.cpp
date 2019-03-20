#include <iostream>
using std::cout; using std::endl;
#include <cstring>
struct Stock
{
    char code[7];
    char market;
    int price;
};

int main()
{
    Stock * pstock = new Stock;
    std::cout << "size: " << sizeof(Stock) << endl;
    strcpy_s(pstock->code, "600000");
    pstock->market = 1;
    pstock->price = 123;
    std::cout << pstock->code << ": " << pstock->market << ": " << pstock->price <<  "_end_ " << std::endl;
    delete pstock;
}