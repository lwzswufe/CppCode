/*
*反向迭代器
*/ 

#include <algorithm>
using std::copy; using std::sort;

#include <iterator>
using std::istream_iterator; using std::ostream_iterator;

#include <vector>
using std::vector;

#include <string>
using std::string; 

#include <fstream>
using std::ifstream; using std::ofstream; 

#include <iostream>
using std::cin; using std::cout; using std::endl;

void print(vector<auto> v)      // 输出字符串
{   
	ostream_iterator<string> out(cout, " ");
    copy(v.begin(), v.end(), out);
    cout << endl;
}

int main()
{
	vector<string> vec;
	string s;
	ifstream input;                         	// 定义读取类
	input.open("read.txt");                    	// 打开文件
	istream_iterator<string> in(input), eof;
	copy (in, eof, back_inserter(vec));

	vector<string> vec2(vec);        			// vec2 is a copy of vec

	print(vec);
	sort(vec.begin(), vec.end()); 				// sorts vec in ``normal'' order
	print(vec);

	sort(vec.rbegin(), vec.rend());				// 逆序排序
	print(vec);

	print(vec2);
	auto it = vec2.begin();

	// rev_it refers one before the first element in vec
	vector<string>::reverse_iterator rev_it(it);
	cout << *(rev_it.base()) << endl; 			// prints first element in vec
	cout << *it << endl;
	cout << *(it + 1) << endl;
	cout << *(rev_it.base() + 1) << endl;  
	cout << *(rev_it - 1) << endl;

	it = vec2.end();
	vector<string>::reverse_iterator rev_it2(it);
	// cout << *it << endl;  // error end() after the last element in vec
	cout << *(it - 1) << endl;
	cout << *(rev_it2) << endl;	
	cout << *(rev_it2 + 1) << endl;				// 反向迭代器的+1指向下一个元素(位置上的前一个元素)
	cout << *(rev_it2.base() - 1) << endl;   
	//cout << *(rev_it) << endl; // error: rev_it refers one before the first element in vec

	return 0;
}
		
