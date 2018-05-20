/*
*/ 

#include <set>
using std::set; using std::multiset;

#include <string>
using std::string;

#include <vector>
using std::vector; 

#include <iostream>
using std::cout; using std::endl; 

#ifndef LIST_INIT
#include <iterator>
using std::begin; using std::end;
#endif

void print(set<auto> iset)
{
	for (auto i : iset)
		cout << i << ", ";
	cout << endl;
}

void print(multiset<auto> iset)
{
	for (auto i : iset)
		cout << i << ", ";
	cout << endl;
}

int main() 
{
	vector<int> ivec;
	for (vector<int>::size_type i = 0; i != 5; ++i) 
	{
	    ivec.push_back(i);
	    ivec.push_back(i);  
	}
	
	set<int> iset(ivec.cbegin(), ivec.cend());
	multiset<int> miset(ivec.cbegin(), ivec.cend());
	
	print(iset);
	print(miset);
	
	// returns an iterator that refers to the element with key == 1
	auto iter = iset.find(1);
	cout << *iter << endl;   
	iter = iset.find(11);			// returns the iterator == iset.end()

	cout << iset.count(1) << endl;  // returns 1
	cout << iset.count(11) << endl; // returns 0

	// // returns an iterator to the first element with key == 1
	cout << "multiset" << endl;
	iter = miset.find(1);
	cout << *iter << endl;   		// 指向被找到的第一个key

	cout << miset.count(1) << endl;  // returns 1
	cout << miset.count(11) << endl; // returns 0
	
	set<string> set1;    			// empty set
	set1.insert("the");  			// set1 now has one element
	set1.insert("and");  			// set1 now has two elements
	print(set1);
	

	set<int> set2;            		// empty set
	int temp[] = {2,4,6,8,2,4,6,8};
	set2.insert(begin(temp), end(temp));
	print(set2);

	int temp2[] = {1,3,5,7,1,3,5,7};
	set2.insert(begin(temp2), end(temp2));
	print(set2);

	return 0;
}
