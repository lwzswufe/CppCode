#include <iostream>
using std::cout; using std::endl;

#include "Read_ini.h"

int main()
{   
    char fn[100] = "TradeX-L2.ini";
    char s1[256] = "[COMMON]\n";
    char s2[256] = "\n";
    char s3[256] = "BakIPADDRESS = 210.51.55.211";
    std::string key, value;
    line_parse(s1, key, value);
    line_parse(s2, key, value);
    line_parse(s3, key, value);
}