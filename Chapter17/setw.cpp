/*
*/ 

#include <iostream>
using std::cout; using std::endl; 
using std::left; using std::right; using std::internal;

#include <iomanip>
using std::setw; using std::setfill;

int main()
{
	int i = -16;
	double d = 3.14159;
									// setw 指定下一个数字或者字符的最小空间
									// pad the first column to use a minimum of 12 positions in the output
	cout << "i: " << setw(12) << i << "next col" << '\n'
	     << "d: " << setw(12) << d << "next col" << '\n';
									// pad the first column and left-justify all columns
	cout << left 					// 左侧填充字符
	     << "i: " << setw(12) << i << "next col" << '\n'
	     << "d: " << setw(12) << d << "next col" << '\n'
	     << right;          	 	// restore normal justification
									// pad the first column and right-justify all columns
	cout << right					// 右侧填充
	     << "i: " << setw(12) << i << "next col" << '\n'
	     << "d: " << setw(12) << d << "next col" << '\n';
									// pad the first column but put the padding internal to the field
	cout << internal				// 在符号和值之间填充
	     << "i: " << setw(12) << i << "next col" << '\n'
	     << "d: " << setw(12) << d << "next col" << '\n';
									// 用#填充
	cout << setfill('#')			// pad the first column, using # as the pad character
	     << "i: " << setw(12) << i << "next col" << '\n'
	     << "d: " << setw(12) << d << "next col" << '\n'
	     << setfill(' ');   		// restore the normal pad character

	return 0;
}
