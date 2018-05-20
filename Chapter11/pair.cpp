/*
*/ 

#include <string>
using std::string;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <algorithm>
using std::sort;

#include <iterator>
using std::istream_iterator; using std::ostream_iterator;

#include <utility>
using std::pair; using std::make_pair;

#include <iostream>
using std::cin; using std::cout; using std::endl;


// three different ways to return a pair
// 1. list initialize the return value
pair<string, int>
process(vector<string> &v)
{
	if (!v.empty())
		return make_pair(v.back(), v.back().size());
	else
		return pair<string, int>();
}

// 2. use make_pair to generate the return value
pair<string, int>
process2(vector<string> &v)
{
	// process v
	if (!v.empty())
		return make_pair(v.back(), v.back().size());
	else
		return pair<string, int>();
}

// 3. explicitly construct the return value
pair<string, int>
process3(vector<string> &v)
{
	// process v
	if (!v.empty())
		return pair<string, int>(v.back(), v.back().size());
	else
		return pair<string, int>();
}

int main()
{
	vector<string> v = {"asda", "dad", "afgda", "rfg"};

	// all three output statements should be the same 
	cout << v.back() << endl;
	auto biggest = process(v);
	cout << biggest.first << " " << biggest.second << endl;
	biggest = process2(v);
	cout << biggest.first << " " << biggest.second << endl;
	biggest = process3(v);
	cout << biggest.first << " " << biggest.second << endl;
	cout << "end" << endl;
}
