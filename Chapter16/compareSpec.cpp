#include <iostream>
using std::cout; using std::endl;

#include <functional>
using std::less;

#include <cstring>
using std::strcmp;


struct complex
{	
	static int create_no;								// 定义静态变量
	friend int operator<(const complex&, const complex&);
	complex(double a_value, double b_value): a{a_value}, b{b_value} 
	{create_no += 1;}
	double a, b;
};
int complex::create_no = 0;								// 非const静态变量必须在类外初始化

int operator<(const complex& c1, const complex& c2)		// 重载< 操作符供less()调用
	{	
		cout << "use override operator '<' " << endl;
		if (c1.a < c2.a and c1.b < c2.b) 
			return 1;
	 	else
	 		return 0;
	}
// version of compare that will be correct even if used on pointers
template <typename T> int compare(const T &v1, const T &v2)
{
	cout << "compare(T)" << "\t";

	if (less<T>()(v1, v2)) return -1;
	if (less<T>()(v2, v1)) return 1;

	return 0;
}
														// 非类型参数必须是常量表达式 可以由编译器推断
template<unsigned N, unsigned M> 						// N, M是非类型参数
int compare(const char (&p1)[N], const char (&p2)[M])
{
	cout << "compare(const char arrays)" << "\t";

	return strcmp(p1, p2);
}

template<> 
int compare(const char *const& p1, const char *const& p2)
{
	cout << "compare(const char*const)" << "\t";

	return strcmp(p1, p2);
}

int main()
{
	int *p1 = new int(45);
	int *p2 = new int(42);
	// because we're comparing pointer values, the result of
	// this call may vary each time the program is run
	cout << compare(*p1, *p2) << endl;					// 指针版本
	cout << compare(p1, p2) << endl;					// 引用版本

	cout << strcmp("hi", "mom") << endl;
	cout << compare("hi", "mom") << endl;

	const char *cp1 = "hi", *cp2= "mom";
	cout << compare(cp1, cp2) << endl;
	
	cout << "we create: " << complex::create_no << " complex " << endl;
	
	complex c1(1.0, 2.0), c2(-1.0, 0.1), c3(0.2, -0.1);

	cout << "we create: " << complex::create_no << " complex " << endl;
	
	compare<complex>(c1, c2);
	compare(c2, c3);

	return 0;
}
