
#include "StrVec.h"

#include <string>
using std::string;

#include <iostream>
using std::cout; using std::endl;
using std::istream;

#include <fstream>
using std::ifstream;

#include <iterator>
using std::begin; using std::end;

void print(const StrVec &svec)
{
	for (auto it : svec)
		cout << it << " " ;
	cout <<endl;
}

StrVec getVec(istream &is)
{
	StrVec svec;
	string s;
	while (is >> s)
		svec.push_back(s);
	return svec;
}
	
int main()
{	
	string temp[] = {"one", "two", "three"};
	cout << "StrVec sv(begin(temp), end(temp))" << endl;
	StrVec sv(begin(temp), end(temp));
									// run the string empty funciton on the first element in sv
	if (!sv[0].empty()) 
		sv[0] = "None"; 			// assign a new value to the first string 

									// we'll call getVec a couple of times
									// and will read the same file each time
	ifstream in("data/storyDataFile");
	cout << "StrVec svec = getVec(in); 依次读取" << endl;
	StrVec svec = getVec(in);

	print(svec);

	in.close();

	cout << "\n\ncopy  auto svec2 = svec;" << svec.size() << endl;
	auto svec2 = svec;
	print(svec2);

	
	cout << "\n\nassign StrVec svec3; svec3 = svec2;" << endl;
	StrVec svec3;
	svec3 = svec2;
	print(svec3);

	cout << "\n\nassign StrVec v1, v2; v1 = v2;" << endl;
	StrVec v1, v2;
	v1 = v2;                   		// v2 is an lvalue; copy assignment

	in.open("data/storyDataFile");
	v2 = getVec(in);          		// getVec(in) is an rvalue; move assignment
	in.close();

	string s = "some string or another";
	print(v1);
	v1.push_back(s);      			// calls push_back(const string&)
	v1.push_back("done"); 			// calls push_back(string&&)
	print(v1);

	s = "the end";

	cout << "v1.push_back(s);" << endl;
	v1.push_back(s); 				// calls push_back(string&&)
	cout << "v1.push_back(s);" << endl;
	v1.push_back(s);               	// calls push_back(const string&)

	string s1 = "the beginning", s2 = s;

	cout << "v1.push_back(string(s1 + s2));" << endl;
 	v1.push_back(string(s1 + s2)); 	// calls push_back(string&&)
	print(v1);
	return 0;
}

