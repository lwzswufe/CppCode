/*
*/ 

#include <iostream>
using std::cout; using std::endl; 

#include <iomanip>
using std::setprecision;

#include <cmath>
using std::sqrt;

int main()
{	// 指定打印精度cout.precision
	// cout.precision reports the current precision value
	cout  << "Precision: " << cout.precision()  
	      << ", Value: "   << sqrt(2.0) << endl;
	
	// cout.precision(12) asks that 12 digits of precision be printed
	cout.precision(12);
	cout << "Precision: " << cout.precision() 
	     << ", Value: "   << sqrt(2.0) << endl;
	
	// alternative way to set precision using the setprecision manipulator
	cout << setprecision(3);
	cout << "Precision: " << cout.precision() 
	     << ", Value: "   << sqrt(2.0) << endl;
	
	return 0;
}
