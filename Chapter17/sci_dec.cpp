/*
*/ 

#include <cmath>
using std::sqrt;

#include <iostream>
using std::cout; using std::endl;
using std::fixed; using std::scientific;
using std::uppercase; using std::nouppercase;
using std::hexfloat; using std::defaultfloat;

int main() 
{
	cout << "default format: " << 100 * sqrt(2.0) << '\n'
		 << "scientific: " << scientific << 100 * sqrt(2.0) << '\n'
	     << "fixed decimal: " << fixed << 100 * sqrt(2.0) << '\n'
		 << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << '\n'
		 << "use defaults: " << defaultfloat << 100 * sqrt(2.0) 
		 << "\n\n";
	
	cout << uppercase		// 将16进制大写显示
	     << "scientific: " << scientific << sqrt(2.0) << '\n'
	     << "fixed decimal: " << fixed << sqrt(2.0) << '\n'
		 << "hexadecimal: " << hexfloat << sqrt(2.0) << "\n\n"
		 << nouppercase;	// 关闭16进制大写显示
	
	return 0;
}
