#include "LocalMath.h"          // 含有函数声明的头文件应该被包含到函数定义的源文件中

                                // return the greatest common divisor
int gcd(int v1, int v2)         //最大公约数
{
    while (v2) {
        int temp = v2;
        v2 = v1 % v2;
        v1 = temp;
    }
    return v1;
}
                                // factorial of val is val * (val - 1) *  (val - 2) . . . * ((val -  (val - 1)) * 1)
int fact(int val)               // 阶乘
{
	int ret = 1;                // local variable to hold the result as we calculate it
	while (val > 1) 
		ret *= val--;           // assign ret * val to ret and decrement val
	return ret;                 // return the result
}

                                // recursive version of factorial:
                                // calculate val!, which is 1 * 2 * 3 . . . * val
int factorial(int val)
{
    if (val > 1)
        return factorial(val-1) * val;
    return 1;
}

