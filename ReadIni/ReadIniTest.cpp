#include "ReadIni.h"
#include <vector>
#include <iostream>
using std::vector;
/*
g++ -std=c++11 Read_ini_test.cpp Read_ini.h Read_ini.cpp -o Read_ini_test && "/home/wiz/CppCode/File/"Read_ini_test
*/
int main()
{   
    IniType conf;
    try
    {
        conf = ReadIni("Trade.ini");
    }
    catch(const std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        return -1;
    }
    ShowIni(conf);
    printf("Read End\n");
    return 0;
}