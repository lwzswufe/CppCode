#include <iostream>

int main()
{
	int i = 0, &ri = i;  // ri是i的引用  ri is a reference to i
	// ri 是i的别名         ri is just another name for i; 
	// ri 的值会绑定为i的值  this statement prints the value of i twice
	std::cout << i << " " << ri << std::endl;

	i = 5; 
	// 改变i同时也会改变i的引用ri的值  changing i is reflected through ri as well
	std::cout << i << " " << ri << std::endl;

	ri = 10; 
	// 改变ri 同时也会改变 i的值
	std::cout << i << " " << ri << " " << std::endl;

	return 0;
}
