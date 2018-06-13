/*
*/ 

#include "Vec.h"

#include <string>
using std::string;

#include <iostream>
using std::cin; using std::cout; using std::endl;
using std::istream;

#include <sstream>
using std::istringstream;

void print(const Vec<string> &svec)
{
	for (auto it : svec)
		cout << it << " " ;
	cout << endl;
}

Vec<string> getVec(istringstream &is)
{
	Vec<string> svec;
	string s;
	while (is >> s)
	{
		svec.push_back(s);
		cout << s << ", ";
	}
	cout << endl;
	return svec;
}
	
int main()
{	
	istringstream str_in("001\n002\n003\n");
	Vec<string> svec = getVec(str_in);
	print(svec);

	cout << "copy " << svec.size() << endl;
	auto svec2 = svec;
	print(svec2);

	cout << "assign" << endl;
	Vec<string> svec3;
	svec3 = svec2;
	print(svec3);

	istringstream str_in2("004\n005\n");

	Vec<string> v1, v2;
	Vec<string> v3 = getVec(str_in2);
	v1 = v2;            		// copy assignment
	v2 = v3;  					// move assignment
	print(v1);
	print(v2);
	print(v3);

	return 0;
}
