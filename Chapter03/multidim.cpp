#include <iterator>
using std::begin; using std::end;

#include <vector>
using std::vector;
#include <iostream>
using std::cout; using std::endl;

#include <cstddef>
using std::size_t;

int main()
{
	
	int ia1[3][4];                                       // 声明一个3*4的数组  值随机
	
	for (auto &row : ia1) 
	{
		for (auto col : row)   
			cout << col << ", ";
		cout << endl;
	}	

	int arr[3][4] = {0};  								// 声明一个3*4的数组  值=0
	
	for (auto &row : arr) 
	{
		for (auto col : row)   
			cout << col << ", ";
		cout << endl;
	}	
	
	ia1[2][3] = arr[0][0];

	int ia2[3][4] = {                                  // 声明数组 并赋值
	    {0, 1, 2, 3},                                  // 第一行
	    {4, 5, 6, 7},   
	    {8, 9, 10, 11}  
	};
	
	int ia3[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
	
	int ia4[3][4] = {{ 0 }, { 4 }, { 8 }};             // 第一列为 0 4 8
	
	for (auto &row : ia4) 
	{
		for (auto col : row)   
			cout << col << ", ";
		cout << endl;
	}	

	cout << " ix: " << endl;
	int ix[3][4] = {0, 3, 6, 9};                      // 第一行为 0 3 6 9
	
	for (auto *ptr_row : ia2)                        // ptr_row 是每行第一个元素的指针
	{	
		for (auto ptr_col = ptr_row; ptr_col != ptr_row + 4;ptr_col++)   
			cout << *ptr_col << ", ";
		cout << endl;
	}	

	for (auto ptr_row = begin(ia2); ptr_row != end(ia2); ptr_row++)   // ptr_row 迭代器
	{	
		for (auto ptr_col = begin(*ptr_row); ptr_col != end(*ptr_row);ptr_col++)   
			cout << *ptr_col << ", ";
		cout << endl;
	}	

	for (auto ptr_row = begin(ia2); ptr_row != end(ia2); ptr_row++)   // ptr_row 迭代器
	{	
		for (auto ptr_col : *ptr_row)   
			cout << ptr_col << ", ";
		cout << endl;
	}	
	
	cout << "iter iter" << endl;
	for (auto ptr_row : ia2)                        // ptr_row 是每行第一个元素的指针
	{	
		auto row = *ptr_row+1;   
		cout << row << endl;
	}	
	cout << "iter iter" << endl;

#ifdef CONSTEXPR_VARS
	constexpr size_t rowCnt = 3, colCnt = 4;
#else
	const size_t rowCnt = 3, colCnt = 4;
#endif
	int ia[rowCnt][colCnt];   // 12 uninitialized elements 
	
    // for each row
    for (size_t i = 0; i != rowCnt; ++i) {
        // for each column within the row
        for (size_t j = 0; j != colCnt; ++j) {
            // assign the element's positional index as its value
            ia[i][j] = i * colCnt + j;   
		}
	}

	// four ways to print the contents of ia
	// 1. using nested range for loops
	for (const auto &row : ia) // for every element in the outer array
		for (auto col : row)   // for every element in the inner array
			cout << col << endl; // print the element's value
    cout << ia[0][0] << ' ' << ia[2][3] << endl; // prints 0 11


	// 2. using pointers and a traditional for loop
	//    with pointer arithmetic to calculate the end pointers 
	for (auto p = ia; p != ia + rowCnt; ++p) {
		// q points to the first element of an array of four ints; 
		// that is, q points to an int
	    for (auto q = *p; q != *p + colCnt; ++q)
	         cout << *q << ' ';
		cout << endl;
	}
	
	// 3. using pointers and a traditional for loop
	//    with the library begin and end functions to manage the pointers
	for (auto p = begin(ia); p != end(ia); ++p) {
		// q points to the first element in an inner array
		for (auto q = begin(*p); q != end(*p); ++q)
			cout << *q << ' ';  // prints the int value to which q points
		cout << endl;
	}
	
	// 4. using a type alias to declare the loop control variable
#ifdef TYPE_ALIAS_DECLS
	using int_array = int[4]; // new style type alias declaration 
#else
	typedef int int_array[4]; // equivalent typedef declaration
#endif

	for (int_array *p = ia; p != ia + 3; ++p) {
	    for (int *q = *p; q != *p + 4; ++q)
	         cout << *q << ' ';
		cout << endl;
	}

	// alternative way to assign positional index to elements 
	// in a two-dimensional array
	int alt_ia[rowCnt][colCnt]; // 12 uninitialized elements 
	size_t cnt = 0;
	for (auto &row : alt_ia)    // for every element in the outer array
		for (auto &col : row) { // for every element in the inner array
			col = cnt;          // give this element the next value
			++cnt;              // increment cnt
		}
	// now print the value of the array
	for (const auto &row : alt_ia) // for every element in the outer array
		for (auto col : row)     // for every element in the inner array
			cout << col << endl;

	return 0;
}
