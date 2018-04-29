#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <string>
using std::string;

int main()
{
    int val1 = 1, val2 = 1, val; 
    cout << "Fibonacci numbers: " << endl;
    do 
    {
        val = val1 + val2;
        cout << "The sum of " << val1 << " and " << val2
             << " = " << val << endl;
        val1 = val2;
        val2 = val;
    } 
    while (val2 <= 300 && val1 < val2);      // 第一次运行时 先执行动作 再判断条件

    cout << "\n\n" << endl;

    val1 = val2 = 1;
    while (val2 <= 300)
    {
        val = val1 + val2;
        cout << "The sum of " << val1 << " and " << val2
             << " = " << val << endl;
        val1 = val2;
        val2 = val;
    } 
	return 0;
}
