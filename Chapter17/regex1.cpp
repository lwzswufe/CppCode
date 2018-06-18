/*
*/ 

#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include <regex>
using std::regex; using std::sregex_iterator; using std::smatch;

int main()
{
	string pattern("[^c]ei");					// find the characters ei that follow a character other than c
												// 定义string类型的正则表达式 查找后接ei的字符
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; // we want the whole word in which our pattern appears
	cout << "parttern: " << pattern << endl;	// 我们需要包含整个单词

	regex r(pattern); 							// 定义一个正则表达式
	smatch results;   							// define an object to hold the results of a search
												// 定义一个对象保存搜索结果

	string test_str = "receipt freind theif receive";  
												// use r to find a match to pattern in test_str
	if (regex_search(test_str, results, r)) 	// if there is a match
		cout << results.str() << endl;      	// print the matching word

	sregex_iterator it(test_str.begin(), test_str.end(), r);
												// 正则表达式匹配迭代器
	sregex_iterator end_it;   					// end iterator
	for ( ; it != end_it; ++it)
		cout << it->str() << endl;     			// print current match

	auto it2 = test_str.cbegin();
	while (it2 != test_str.cend() && 
	       regex_search(it2, test_str.cend(), results, r)) 
	{
		cout << results.str() << endl;
		it2 += results.prefix().length() + results.length();
	
	}

	return 0;
}
