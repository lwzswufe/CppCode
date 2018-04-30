// 使用const形参

#include <iostream>
using std::endl; using std::cout;

#include <iterator>
using std::begin; using std::end;

                                        // prints a null-terminated array of characters
void print(const char *cp)              // 打印字符串
{                                       // 字符串最后一个字符后面跟着一个空字符
	if (cp)                             // if cp is not a null pointer
		while (*cp)                     // so long as the character it points to is not a null character
			cout << *cp++;              // print the character and advance the pointer
	cout << endl;
}

                                        // print ints in the given range
void print(const int *beg, const int *end) 
{										// 打印数组
										// print every element starting at beg up to but not including end
    									//(*beg)++; 错误  read-only 不能修改*beg的数值
	while (beg != end) 
        cout << *beg++ << " "; 			// print the current element 
		                       			// and advance the pointer
	cout << endl;
}

void print(const int *beg, size_t size) 
{										// 打印数组
										// print every element starting at beg up to but not including end
    for (size_t sz = 0;sz < size; sz++)
        cout << *beg++ << " "; 			// print the current element 
		                       			// and advance the pointer
	cout << endl;
}

int main() 
{
	print("hi world!"); 				// calls first version of print
										// j is converted to a pointer to the first element in j
										// the second argument is a pointer to one past the end of j
    int j[5] = {0, 1, 8, 9, 10};  
    print(begin(j), end(j));  			// library begin and end functions
										// equivalent call, directly calculate the begin and end pointers
	print(j, j + 2); 
	print(j, 5); 

    return 0;
}
