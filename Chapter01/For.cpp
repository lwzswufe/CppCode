#include <iostream>

using namespace std;

int main()
{   
    int sum = 0;
    for (int i = -10; i <= 10; ++i)// 初值 终止条件 迭代表达式
    {
        sum += i;
        cout << "i: " << i << " sum: " << sum << endl;
    }
    cout << "The Sum is :" << sum << endl;
    return 0;
}