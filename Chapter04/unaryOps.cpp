// 逻辑和关系运算符

#include <iostream>
using std::cout; using std::endl;

int main()
{
	int i = 1024;
	int k = -i;               // i is -1024
	
	bool b = true;
	bool b2 = -b;             // b2 is true!

	int c = b + 1;            // c is 2
	bool c2 = c - 2;          // c2 is false
	
	cout << b << " " << b2 << " " << endl;
	cout << c << " " << c2 << " " << endl;

	int f, g;                 // 赋值运算满足左右结合律
	f = g = 0;

	return 0;
}
