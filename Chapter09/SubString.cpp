
#include <string>
using std::string;

#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

void print_str(string str)
{
    size_t pos_st = 0, len = str.size(), pos_ed;
    int flag = 0;
    do
    {   
        flag++;
        pos_ed = str.find("\n", pos_st);
        if (pos_ed == 0 || pos_ed > len)
            pos_ed = len;
        cout << str.substr(pos_st, pos_ed - pos_st);
        // cout << pos_st << ":" << pos_ed << ":" << len << "___"; 
        pos_st = pos_ed + 1;
    }
    while (pos_st < len && flag < 4);
    cout << endl;
}

int main()
{   
    string str1 = "Hello World!\n", str2 = "Hello \nWorld!", str3 = "Hello \nWorld!\n", str4 = "Hello World!";
    print_str(str1);
    print_str(str2);
    print_str(str3);
    print_str(str4);
    return 0;
}