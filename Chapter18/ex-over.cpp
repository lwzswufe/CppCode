/*
*/ 

#include <iostream>
using std::cout; using std::endl;

namespace primerLib 
{
    void compute() { cout << "primerLib::compute()" << endl; }
	void compute(const int * ptr) 
	   { cout << "primerLib::compute(const int *):" << *ptr << endl; }
    void compute(const void *) 
	   { cout << "primerLib::compute(const void *)" << endl; }
}

// brings comput() and compute(const void*) into scope
using primerLib::compute;

void compute(int c) { c += 1; cout << "compute(int):"<< c << endl; }
void compute(double, double = 3.4)
	   { cout << "compute(double, double)" << endl; }
void compute(char*, char* = 0)
         { cout << "compute(char*, char*)" << endl; }

int main()
{
	int i = 42;
	double d = 0.16;
	char c = 'a';
	cout << &i << endl;
	compute(i);  // compute(int)
	compute(c);  // compute(int) char c 隐式转换为int 97
	compute(&i); // primerLib::compute(const int*)
	compute(&d); // primerLib::compute(const void*) 匹配到指针类型
	compute(&c); // compute(char*, char*)
	compute(3.4);// compute(double, double)
	
	return 0;
}
