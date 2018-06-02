/*
*/ 

#include <vector>
using std::vector;

#include <iterator>
using std::inserter;

#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <algorithm>
using std::transform;

struct absInt 
{							//类型转换运算符
    int operator()(int val) const 
	{
        return val < 0 ? -val : val;
    }
};

int main() {
    int i = -42;
    absInt absObj;           // object that has a function-call operator
    unsigned ui = absObj(i); // passes i to absObj.operator()
    cout << i << " " << ui << endl;

							// store collection of positive and negative integers in vi
	vector<int> vi{-1, 2, 5, 7, -88};

							// call absInt to store the absolute value of those ints in vu
	vector<unsigned> vu;
	transform(vi.begin(), vi.end(), back_inserter(vu), absInt());

							// print contents of vu using a lambda
	for_each(vu.begin(), vu.end(), [](unsigned i) { cout << i << " "; });
	cout << endl;

	vector<unsigned> vu2;
							// similar transformation but using a lambda
	transform(vi.begin(), vi.end(), back_inserter(vu2),
	          [](int i) { return i < 0 ? -i : i; });
	if (vu == vu2)
		cout << "as expected" << endl;
	else {
		cout << "something's wrong, vectors differ" << endl;
		for_each(vu.begin(), vu.end(), [](unsigned i) { cout << i << " "; });
	}
	cout << endl;

    return 0;
}
