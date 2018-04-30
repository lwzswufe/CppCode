// 局部静态对象

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout; using std::endl;

size_t count_calls()
{                                         // 第一次调用时初始化 
	static size_t ctr = 0;                // value will persist across calls
	return ++ctr;
}

int main() 
{
	for (size_t i = 0; i != 10; ++i)
		cout << count_calls() << endl;
	return 0;
}
