/*
*/ 

#include "debug_rep.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout; using std::endl;

#include <iterator>
using std::begin; using std::end;

int main()
{
	int temp[] = {1,2,3,4,5,6,7,8,9};
	vector<int> v(begin(temp), end(temp));

	string s("hi");
	cout << debug_rep(v) << endl;			// vector模板->begin-end模板->const_&T模板
	cout << debug_rep(s) << endl; 			// const string& 非模板
	cout << debug_rep("hi") << endl;		// const char* 非模板->const string& 非模板
	cout << debug_rep(&v[0]) << endl;		// const_&*模板->const_&T模板
	cout << debug_rep(&s) << endl;			// const_&*模板
	const string *sp = &s;
	cout << debug_rep(sp) << endl;			// const_&*模板

	char carr[] = "bye";            		// calls pointer version if no overloads
	cout << debug_rep(carr) << endl;		// const char* 非模板->const string& 非模板

	string temp2[] = {"Proust", "Shakespeare", "Barth" };
	vector<string> authors(begin(temp2), end(temp2));
	const char* temp3[] = {"Proust", "Shakespeare", "Barth" };
	vector<const char*> authors2(begin(temp3), end(temp3));

	cout << debug_rep(authors) << endl;		// vector模板->begin-end模板->const string& 非模板
	cout << debug_rep(authors2) << endl;	// vector模板->begin-end模板->const char* 非模板->const string& 非模板
	cout << debug_rep(s) << endl;			// const string& 非模板
	s += "more stuff";
	cout << debug_rep(s) << endl;			// const string& 非模板
	s += "\\escape\"and quotes";
	cout << debug_rep(s) << endl;			// const string& 非模板

	cout << debug_rep("hi world!") << endl; // const char* 非模板->const string& 非模板

	s = "hi";
	const char *cp = "bye";
	char arr[] = "world";

	cout << debug_rep(s) << endl;  			// calls specialization debug_rep(const string&
	cout << debug_rep(cp) << endl; 			// calls specialization debug_rep(const char*
	cout << debug_rep(arr) << endl;			// calls specialization debug_rep(char*
	cout << debug_rep(&s) << endl; 			// calls template debug_rep(T*)

	return 0;
}
