#include "Read_ini.h"
#include <vector>
using std::vector;
/*
g++ -std=c++11 Read_ini_test.cpp Read_ini.h Read_ini.cpp -o Read_ini_test && "/home/wiz/CppCode/File/"Read_ini_test
*/
int main()
{   
    IniType conf = Read_ini("Trade.ini");
    show_ini(conf);
    printf("Read End\n");
    return 0;
}