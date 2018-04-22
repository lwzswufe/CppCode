#include<iostream>

using namespace std;

int main()
{   
    int sum = 0, val = 1;
    while (val <= 10)
    {
        cout << "iter:" << val << endl;
        sum += val;
        ++val;
    }
    cout << "The Sum is :" << sum << endl;
    return 0;
}