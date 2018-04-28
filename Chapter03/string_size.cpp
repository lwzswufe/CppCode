#include <iostream>
using std::cout; using std::endl; using std::string;

string st1;           // empty string
string st2(st1);      // st2 is a copy of st1
string st3(7, 'c');   // n个重复的字符

int main()
{
    string st("The expense of spirit\n");
    cout << "The size of " << st << "is " << st.size()
         << " characters, including the newline" << endl;
    cout << st3 << endl;
    cout << true << endl;
    if (st1 == st2)
    {
        cout << "st1 == st2 " << endl;
    }
    cout << st2[8] << st2[9] << endl;
    return 0;
}
