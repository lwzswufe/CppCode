#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

int main()
{
    string var{"Cambridge"};
    string f;

    string &r1 {var};
    string &r2 = var;

    cout << r1 << endl;
    cout << r2 << endl;

    //string&& rr2 {var};    // 错误
    string&& rr3 {"Oxford"};
    cout << rr3 << endl;
    
}