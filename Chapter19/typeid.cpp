/*
获取指定类型的信息
*/ 

#include <iostream>
using std::cout; using std::endl;

#include <typeinfo>

#include <string>
using std::string;

struct Base {
    virtual ~Base() { }
};

struct Derived : Base { };

int main()
{
	int arr[10];							// 数组大小不一样 类型也会不一样
	int arr2[11];
	int* int_p = arr;						// 数组首字母的地址
	auto arr_p1 = &arr;						// 数组的地址
	int (*arr_p2)[10] = &arr;				// 数组的地址
	Derived d;
	Base *p = &d;
	string s = "word";
	char char_arr[11] {"0123456789"};
	char (*char_arr_ptr)[11] = &char_arr;
	char* c_ptr = char_arr;
	const char const_char[11]{"const char"};// 忽略顶层const
	const char* const_char_ptr = const_char;// 底层const不会忽略
	
	cout << "int:          " << typeid(42).name() << endl
		 << "int*:         " << typeid(int_p).name() << endl
	     << "arr[int]:     " << typeid(arr).name() << endl
		 << "arr[int]*:    " << typeid(arr_p1).name() << endl
		 << "arr[int]*:    " << typeid(arr_p2).name() << endl
		 << "arr[char]:    " << typeid(char_arr).name() << endl
		 << "arr[char]*:   " << typeid(char_arr_ptr).name() << endl
		 << "char*:        " << typeid(c_ptr).name() << endl
		 << "constchar:    " << typeid(const_char).name() << endl
		 << "constchar_ptr:" << typeid(const_char_ptr).name() << endl
	     << "Base:         " << typeid(d).name() << endl
	     << "string:       " << typeid(std::string).name() << endl
		 << "string:       " << typeid(s).name() << endl
		 << "string:       " << typeid(s).name() << endl
	     << "Base_ptr:     " << typeid(p).name() << endl
	     << "Derived:      " << typeid(*p).name() << endl;
	
	if (typeid(const_char) == typeid(char_arr))
		cout << "const char has same type with char "<< endl;

	if (typeid(const_char_ptr) != typeid(c_ptr))
		cout << "const char* don't has same type with char* "<< endl;

	if (typeid(arr) != typeid(arr2))
		cout << "arr[11] don't has same type with arr[12] "<< endl;
	return 0;
}
