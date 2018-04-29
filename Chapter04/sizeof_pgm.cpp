// sizeof 运算符返回一条表达式或一个类型名字所占用的字节数
#include <iostream>
using std::cout; using std::endl;

int main() 
{
	int data;
	unsigned c = sizeof data; 
	
	cout << "short: " << sizeof(short) << "\n"        // 2
	     << "short[3]: " << sizeof(short[3]) << "\n"  // 6
	     << "short*: " << sizeof(short*) << "\n"      // 8
	     << "short&: " << sizeof(short&) << endl;     // 2
	
	cout << endl; 
	
	cout << "int: " << sizeof(int) << "\n"            // 4
	     << "int[3]: " << sizeof(int[3]) << "\n"      // 12
	     << "int*: " << sizeof(int*) << "\n"          // 8
	     << "int&: " << sizeof(int&) << endl;         // 4
	
	cout << endl; 

	int x[10];   
	int *ip = x;

	// number of elements in x
	cout << sizeof(x)/sizeof(*x) << endl;             // 10

	// divides sizeof a pointer by sizeof an int
	cout << sizeof(ip)/sizeof(*ip) << endl;           // 2
	
	return 0;
}
