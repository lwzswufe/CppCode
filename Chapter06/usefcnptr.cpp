/*
使用函数指针
*/
#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

// function to return minimum element in an vector of ints
int min_element(vector<int>::iterator, 
                vector<int>::iterator);

// pointer to function, initialized to point to min_element
int (*pf)(vector<int>::iterator, vector<int>::iterator)   // 定义函数指针
        = min_element;

int main() 
{
    vector<int> ivec;
    // give ivec some values
    cout << "Direct call: "                               // 直接调用
         << min_element(ivec.begin(), ivec.end()) << endl;

    cout << "Indirect call: "                             // 通过指针调用
         << pf(ivec.begin(), ivec.end()) << endl;

	cout << "equivalent indirect call: "                  // 等效直接调用
	     << (*pf)(ivec.begin(), ivec.end()) << endl;

    return 0;
}

// returns minimum element in an vector of ints
int min_element(vector<int>::iterator beg, 
                vector<int>::iterator end) {
    int minVal = 0;
    while (beg != end) {
        if (minVal > *beg)
            minVal = *beg;
        ++beg;
    }
    return minVal;
}

