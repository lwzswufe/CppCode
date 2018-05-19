/*
 * 求和
 */

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <algorithm>
using std::fill; using std::fill_n;

#include <numeric>
using std::accumulate;

#include <iterator>
using std::back_inserter;

#include <fstream>
using std::ifstream; 

#include <iostream>
using std::cin; using std::cout; using std::endl;


void print(vector<auto> v)      // 输出字符串
{   
    cout << "vec: ";
    for(auto iter : v)
        cout << iter << ", ";
    cout << endl;
}


int main()
{
	vector<int> vec(10);              			// default initialized to 0
	fill(vec.begin(), vec.end(), 1);  			// reset each element to 1

												// 求和 并设置初值为0
	int sum = accumulate(vec.cbegin(), vec.cend(), 0);
	cout << sum << endl;
	
	print(vec);
	fill(vec.begin(), vec.begin() + vec.size()/2, 10);

	print(vec);
	fill_n(vec.begin(), vec.size()/2, 0);
	

	print(vec);
	fill_n(back_inserter(vec), 10, 42);			// 插入迭代器 从vec的尾部开始插入
	print(vec);

	vector<string> v;
	string s;
	ifstream input;                         	// 定义读取类
    input.open("read.txt");                    	// 打开文件

	while (input >> s)
		v.push_back(s);
	string concat = accumulate(v.cbegin(), v.cend(), string("string: "));
	cout << concat << endl;
	
	return 0;
}

