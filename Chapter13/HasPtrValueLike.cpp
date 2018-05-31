/*
*/ 
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

#include <string>
using std::string; 

							// value-like implementation of HasPtr
class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const string &s = string()): 
		ps(new string(s)), i(0) 
		{ cout << "拷贝构造函数" << endl;}

							// each HasPtr  has its own copy of the string to which ps points
    HasPtr(const HasPtr &p): //函数传参的时候会调用此函数
		ps(new string(*p.ps)), i(p.i) 
		{cout << "拷贝赋值函数" << endl; }

	HasPtr& operator=(const HasPtr &);

	~HasPtr() 
	{ cout << "回收对象 递减引用计数 " << endl;
	  delete ps; }
	  
private:
    string *ps;
    int    i;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{	cout << "swap" << endl;
	using std::swap;
	swap(lhs.ps, rhs.ps); 	// swap the pointers, not the string data
	swap(lhs.i, rhs.i);   	// swap the int members
}

HasPtr& HasPtr::operator=(const HasPtr &rhs) 
{	cout << "赋值运算符_const" << endl;
	auto newp = new string(*rhs.ps);  // copy the underlying string
	delete ps;       		// free the old memory
	ps = newp;       		// copy data from rhs into this object
	i = rhs.i;
	return *this;    		// return this object
}

HasPtr f(HasPtr hp)  		// HasPtr passed by value, so it is copied
{	cout << "function f" << endl;
	HasPtr ret = hp; 		// copies the given HasPtr
							// process ret
	cout << "function end" << endl;
	return ret;      		// ret and hp are destroyed
}

int main()
{ 
	HasPtr h("hi mom!"), h2;// allocates a new copy of "hi mom!"
	cout << "h2 = h" << endl;
	h2 = h;
	cout << "f(h)" << endl;
	f(h);  					// copy constructor copies h in the call to f
		   					// that copy is destroyed when f exits
} 			 				// h is destroyed on exit, which destroys its allocated memory
