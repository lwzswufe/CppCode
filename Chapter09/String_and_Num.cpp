
#include <string>
using std::string; using std::to_string;

#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

int main()
{   
    int i = 124;
    string s = to_string(i);        // 各种类型的数字转字符串
    cout << s << endl;

    s = "6.3254";
    double d = stod(s);             // 字符串转数字
    cout << d << endl;              // stox 
                                    // x = i    int
                                    // x = l    long
                                    // x = ul   unsigned long
                                    // x = ll   long long
                                    // x = ull  unsigned long long
                                    // x = f    float
                                    // x = d    double
                                    // x = ld   long double
    return 0;
}