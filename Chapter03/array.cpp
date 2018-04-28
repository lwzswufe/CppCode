#include <iterator>
using std::begin; using std::end;

#include <vector>
using std::vector;

#include <iostream>
using std::string; using std::cout; using std::endl;

#include <cstddef>                            // size_t
using std::size_t;

int main()
{   
    const unsigned sz = 4;
    int array_1[sz] = {0, 1, 2, 3};

    int array_2[] = {0, 1, 2, 3};
    
    int array_3[5] = {0, 1, 2, 3};     // 数组定义长度大于等于初始赋值数据的长度

    string array_4[3] = {"one", "two"};

    cout << "arr:" << endl;
	for (auto i : array_1)
		cout << i << ", ";
	cout << endl;

    char a1[] = {'C', 'p', 'p'};
    char a2[] = {'C', 'p', 'p', '\0'};
    char a3[] = "Cpp";                 // a3的长度为4 cpp会默认在最后一个字符后面加一个元素 '\0'
    int c = a3[3] + 1;
    cout <<  c << endl;

    int *ptrs[sz];                     // *ptrs 是含有10个int指针的数组
    int (*Parr)[sz] = &array_1;        // Parr指向 array_1
    int (&Refarr)[sz] = array_1;       // Refarr 是array_1 的引用

    return 0;
}
