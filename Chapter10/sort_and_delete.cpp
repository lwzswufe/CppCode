/*
* 排序 指定排序算法
*/ 
#include <string>
using std::string;

#include <algorithm>
using std::sort;

#include <vector>
using std::vector; 

#include <iostream>
using std::cout; using std::cin; using std::endl;

#include <fstream>
using std::ifstream; 

void print(vector<auto> v)      // 输出字符串
{   
    cout << "vec: ";
    for(auto iter : v)
        cout << iter << ", ";
    cout << endl;
}

int compare_string(const string &s1, const string &s2)
{
	if (s1.size() == s2.size())
		return s1 < s2;
	else
		return s1.size() < s2.size();
}

int main() 
{
    vector<string> v;
	string s;
	ifstream input;                         	// 定义读取类
    input.open("read.txt");                    	// 打开文件

	while (input >> s)
		v.push_back(s);

	print(v);
	sort(v.begin(), v.end(), compare_string); 
	print(v);

	auto end_unique = unique(v.begin(), v.end());
	print(v);									// unique 重排序列使重复值排到后面	
												// 重复的元素显示为空

	v.erase(end_unique, v.end());
	print(v);									// 删除元素	真正的删除元素			
	return 0;
}
