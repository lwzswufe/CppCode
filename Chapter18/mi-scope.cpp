
#include <string>
#include <vector>
#include <iostream>

/*
继承类方法的调用
Derived -> Base1
MI -> Derived -> Base1
MI -> Base2
*/
struct Base1 
{
    void print(int) const     // public by default
		{ std::cout << "Base1::print(int) " << ival << std::endl; }
protected:

	int ival;
public:
	Base1(): ival(1) { }
};

struct Base2 
{
    void print(double) const        // public by default
		{ std::cout << "Base2::print(double) " << ival << std::endl; }
protected:
	int ival;
public:
	Base2(): ival(2) { }
};

struct Derived : public Base1 
{
    void print(std::string) const   // public by default
		{ std::cout << "Derived::print(string) " << ival << std::endl; }
protected:
	int ival;
public:
	Derived(): ival(3) { }
};

struct MI : public Derived, public Base2 
{
    void print(std::vector<double>) 
		{ std::cout << "MI::print(int(vector<double>) " 
			        << ival << std::endl; }
protected:
	int ival;
public:
	MI(): ival(4) { }
};

int main()
{
	MI obj;
	obj.Base1::print(0);				// 使用父类 Base1的方法
	obj.Base2::print(3.14);				// 使用父类 Base2的方法
	obj.Derived::print("hi");			// 使用父类 Derived的方法
	obj.print(std::vector<double>());	// 自己定义的方法
	
	return 0;
}
