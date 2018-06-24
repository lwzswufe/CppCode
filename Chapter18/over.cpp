
#include <string>
using std::string;

#include <iostream>

namespace libs_R_us 
{
    extern void print(int) 
		{ std::cout << "libs_R_us::print(int)" << std::endl; }
    extern void print(double) 
		{ std::cout << "libs_R_us::print(double)" << std::endl; }
}

// ordinary declaration
void print(const std::string &)
{
	std::cout << "print(const std::string &)" << std::endl;
}

// this using directive adds names to the candidate set for calls to print:
using namespace libs_R_us;  

// the candidates for calls to print at this point in the program are:
//     print(int) from libs_R_us
//     print(double) from libs_R_us
//     print(const std::string &) declared explicitly

int main()
{
	int ival = 42;
    print("Value: "); 			// calls global print(const string &)
    print(ival);      			// calls libs_R_us::print(int)
	libs_R_us::print(0.23);		// 显示指定调用libs_R_us的方法

	return 0;
}

