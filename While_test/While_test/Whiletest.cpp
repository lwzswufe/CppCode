#include "stdafx.h";
#include <iostream>


int add(int a, int b)  //子程序add 输入变量类型a=int b=int  子函数应位于main函数前
{
	int z;
	z = a + b;
	return z;
}


int main()
{
	std::cout << u8"程序启动" << std::endl;
	int sum = 0, val = 1;
	// keep executing the while as long as val is less than or equal to 10
	while (val <= 10) {
		sum = add(sum, val);  // assigns sum + val to sum
		++val;       // add 1 to val
	}
	std::cout << "Sum of 1 to 10 inclusive is "
		<< sum << std::endl;

	return 0;
}



