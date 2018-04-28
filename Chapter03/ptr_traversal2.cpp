#include <iterator>
using std::begin; using std::end;

#include <cstddef>
using std::size_t; 

#include <iostream>
using std::string; using std::cout; using std::endl;

#include <vector>
using std::vector;

int main()
{
	int ia[] = {0,1,2,3,4,5,6,7,8,9};

	int *p = ia;                             	// p points to the first element in ia
	cout << "use point to print arr[0] " << *p << endl;
	++p;                                      	// p points to ia[1]
	cout << "use point to print arr[1] " << *p << endl;

	int *e = &ia[10]; 							// pointer just past the last element in ia
	cout << "buffer overflow: index out of bound: "
	     << *e << ia[11] << endl;               // 下标越界 引发缓冲区溢出错误  不会报错！

	for (int *b = ia; b != e; ++b)				
		cout << *b << ", "; 					// print the elements in ia
	cout << endl;

	const size_t sz = 10;
	int arr[sz];  								// array of 10 ints

	cout << "arr:" << endl;
	for (auto i : arr)
		cout << i << ", ";
	cout << endl;

												// pbeg points to the first and 
												// pend points just past the last element in arr
	int *pbeg = begin(arr),  *pend = end(arr);

												// find the first negative element, 
												// stopping if we've seen all the elements
	while (pbeg != pend && *pbeg >= 0)
		++pbeg;
	if (pbeg == pend)
		cout << "no negative elements in arr" << endl;
	else
		cout << "first negative number was " << *pbeg << endl;

	string s("some string");

	for(auto s_end = end(s);s_end != begin(s); --s_end)
		cout << *s_end;
	cout << endl;

	for(auto s_beg = s.begin();s_beg != s.end(); ++s_beg)
	{
		// cout << *s_beg;
		char c = *s_beg;
		cout << c;
		if (isspace(*s_beg))
		{
			cout << " blank ";
		}
	}
	cout << endl;

	vector<string> strs{"one", "two", "three", "four"};

	for(auto s_beg = strs.begin();s_beg != strs.end(); ++s_beg)
	cout << *s_beg << " size " << (*s_beg).size() << endl;  // (*s_beg).size() 先解引用 再调用方法

	for(auto s_beg = strs.begin();s_beg != strs.end(); ++s_beg)
	cout << *s_beg << " size " << s_beg->size() << endl;   // s_beg->size() -> 访问成员方法

	return 0;
}

