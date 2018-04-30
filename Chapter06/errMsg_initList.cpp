// initlist 实参数量未知 实参类型相同
// INITIALIZER_LIST 不可修改  vector可修改
#include <vector>
using std::vector;

#include <string>
using std::string; 

#include <iostream>
using std::cout; using std::endl;

#ifdef INITIALIZER_LIST
#include <initializer_list>
using std::initializer_list;
#endif

#ifdef INITIALIZER_LIST
// overloaded version takes only a list of strings
void error_msg(initializer_list<string> il)
{
	for (auto beg = il.begin(); beg != il.end(); ++beg)
		cout << *beg << " " ;
	cout << endl;
}
#else
// overloaded version that takes only pointers to a range of strings
void error_msg(const string *beg, const string *end)
{
	while (beg != end)
		cout << *beg++ << " " ;
	cout << endl;
}
#endif
	
int main()
{
	string expected = "description", actual = "some other case";
#ifdef INITIALIZER_LIST
	initializer_list<int> li = {0,1,2,3};
#else
	vector<int> li;
	for (int i = 0; i < 4; ++i)
		li.push_back(i);
#endif

	// expected, actual are strings 
	if (expected != actual)
#ifdef INITIALIZER_LIST
		error_msg({"function1", expected, actual});
#else
	{ 	
		string ss = "function2";
		const string arr[] = {ss, expected, actual};
		error_msg(begin(arr), end(arr)); 
	}
#endif
	else
#ifdef INITIALIZER_LIST
		error_msg({"functionX3", "okay"});
#else
	{   
		const string arr[] = {"functionX4", "okay"};
		error_msg(begin(arr), end(arr)); 
	}
#endif
	
	// can pass an empty list, calls second version of error_msg
#ifdef INITIALIZER_LIST
	error_msg({}); // prints blank line
#else
	error_msg(nullptr, nullptr);   // prints blank line
#endif
}

