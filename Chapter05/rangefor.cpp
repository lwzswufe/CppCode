#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iterator>
using std::begin; using std::end;

int main()
{
	vector<int> v = {0,1,2,3,4,5,6,7,8,9, 10, 11};
	auto *p = &v[0];
	cout << "local: " << p << " value: " << *p << endl;
	cout << "local: " << p+1 << " value: " << *(p+1) << endl;

	int size = sizeof(v) / sizeof(v[0]);
	cout << " size v: " << sizeof(v)
	     << " size v[0] " << sizeof(v[0]) << endl;

	for (int *ptr = &v[0];ptr != &v[size];ptr++)
		cout << *ptr << " ";
	cout << endl;

	for (auto ptr = begin(v);ptr != end(v);ptr++)
		cout << *ptr << " ";
	cout << endl;

	for (auto &r : v)    // for each element in v
	{
		r *= 2;          // double the value of each element in v
		cout << r << " ";
	}
	cout << endl;

	for (int r : v)
		cout << r << " "; 
	cout << endl;

	return 0;
}
