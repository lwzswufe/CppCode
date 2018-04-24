#include <iostream>

int reused = 42;                               // reused 拥有全局作用域

int main()
{
	int unique = 0;                            // unique 拥有块作用域 block scope

	// output #1: uses global reused; prints 42 0
	std::cout << reused << " " << unique << std::endl;   

	int reused = 0;                            // 覆盖全局作用域

	// output #2: uses local reused; prints 0 0
	std::cout << reused << " " <<  unique << std::endl;  

	// output #3: explicitly requests the global reused; prints 42 0
	std::cout << ::reused << " " <<  unique << std::endl;  // 显示访问全局作用域

	return 0;
}
