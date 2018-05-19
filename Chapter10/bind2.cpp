/*
*
*/ 

#include <algorithm>
using std::for_each;

#include <functional>
using std::bind; using namespace std::placeholders;
using std::ref;

#include <iterator>
using std::istream_iterator; using std::ostream_iterator;

#include <vector>
using std::vector;

#include <string>
using std::string; 

#include <iostream>
using std::cout; using std::cin; using std::endl;
using std::ostream; 

#include <fstream>
using std::ifstream; using std::ofstream; 


ostream &print(ostream &os, const string &s, char c)
{
	return os << s << c;
}

int main()
{
	vector<string> words;
	string s;
	ifstream input;                         	// 定义读取类
    input.open("read.txt");                    	// 打开文件

	while (input >> s)
		words.push_back(s);

	for_each(words.begin(), words.end(), 		// 访问每一个元素
	         bind(print, ref(cout), _1, ','));
	cout << endl;

	auto b = bind(print, ref(cout), _1, ' ');	// 通用函数值适配器

	for_each(words.begin(), words.end(), 
	         b);
	cout << endl;

	ostream_iterator<string> out_iter(cout, " ");
	for (auto word: words)
		*out_iter++ = word;						// 这里的解引用* 递增运算符++可以忽略
	cout << endl;

	ostream_iterator<string> out_iter2(cout, " ");
	for (auto word: words)
		out_iter2 = word;
	cout << endl;

	copy(words.begin(), words.end(), out_iter);


	ofstream os("write.txt");
	for_each(words.begin(), words.end(), 
	         bind(print, ref(os), _1, ' '));	// 不能直接使用os 因为os不可拷贝
	os << endl;

	ifstream is("write.txt");
	istream_iterator<string> in(is), eof;		// 输入流迭代器
	for_each(in, eof, bind(print, ref(cout), _1, '\n'));
	cout << endl;

	return 0;
}
