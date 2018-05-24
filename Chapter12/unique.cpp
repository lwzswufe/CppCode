
#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

#include <string> 
using std::string;

#include <memory>
using std::shared_ptr;using std::unique_ptr;

#define print(x) cout << #x << ": " << x << endl;   

int main() 
{
	unique_ptr<string> p1(new string("Hello!"));
	//unique_ptr<string> p2(p);    // unique_ptr 不支持拷贝
	unique_ptr<string> p3;

	print(*p1);
	string* p2 = p1.release();		// 释放对指针的控制权p1，将其转移给p2 但不会释放内存
	print(*p2);
	delete(p2);						// 释放内存

	string* p_str = new string {"sdada"};
									// 若不使用new(动态分配的对象 会内存错误)
	print(p_str);
	p3.reset(p_str);				// 将智能指针重置 指向内置指针
	print(*p3);
	print(p_str);
	*p_str += "_add";				// 通过内置指针可以继续操作智能指针指向的对象
	print(*p_str);
	print(*p3);
	p3.reset();
	return 0;
}
