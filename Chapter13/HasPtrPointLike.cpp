/*
*/ 

// reference counted version of HasPtr
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

#include <string>
using std::string;

#include <cstddef>

class HasPtr {
public:
							// constructor allocates a new string and a new counter, 
							// 拷贝构造函数
							// which it sets to 1
    HasPtr(const string &s = string()): 
	  ps(new string(s)), i(0), use(new std::size_t(1)) 
	  { show();
		cout << "拷贝构造函数" << endl;}

							// copy constructor copies all three data members 
							// 拷贝赋值函数
							// and increments the counter
    HasPtr(const HasPtr &p): 
		ps(p.ps), i(p.i), use(p.use) 
		{ ++*use; 
		  show();
		  cout << "拷贝赋值函数" << endl;}

	HasPtr& operator=(const HasPtr&);

	HasPtr &operator=(HasPtr&&);

	~HasPtr();

	void print()
	{ cout << "value: " << *ps << " use: " << *use << endl;};
							// move constructor takes over the pointers from its argument
							// and makes the argument safe to delete
	HasPtr(HasPtr &&p): ps(p.ps), i(p.i), use(p.use) 
		{ p.ps = 0; 
		  p.use = 0; 
		  show();
		  cout << "拷贝" << endl;
		}

private:
	void show();
    string *ps;
    int    i;
	std::size_t *use;  		// member to track how many objects share *ps
};

HasPtr::~HasPtr()			// 析构函数
{	
	cout << "回收对象 递减引用计数 " << *use << endl;
	if (--*use == 0) 		// if the reference count goes to 0
	{  	
		//cout << *ps << endl;
		show();
		cout << "reference is 0 delete the string" << endl;
		//delete ps;       	// delete the string
		//delete use;      	// and the counter
	}
}

HasPtr &
HasPtr::operator=(HasPtr &&rhs)
{
	if (this != &rhs) 		// 函数完成析构临时变量-赋值返回变量时会调用这个函数
	{
		if (--*use == 0) 	// 递减临时变量引用次数
		{   				// do the work of the destructor
			cout << *use;	// 删除临时变量
			cout << " delete object" << endl;
			delete ps;
			delete use;
		}
		show();
		cout << "赋值运算符__函数返回" << endl;
		ps = rhs.ps;         // do the work of the move constructor
		i = rhs.i;
		++*rhs.use;
		use = rhs.use;
		ps = 0; 
		use = 0;
	}
	return *this;
}

HasPtr& HasPtr::operator=(const HasPtr &rhs) 
{							// 递增右值对象引用次数
	++*rhs.use;  			// increment the use count of the right-hand operand
	if (--*use == 0) 		// 递减左值对象引用次数
	{   cout << *use;		// then decrement this object's counter
		cout << " delete object const" << endl;
		delete ps;       	// if no other users 
		delete use;      	// free this object's allocated members
	}						// 删除对象 释放内存
	ps = rhs.ps;         	// copy data from rhs into this object
	i = rhs.i;
	use = rhs.use; 
	show();
	cout << "赋值运算符_const"<< endl;
	return *this;        	// return this object
}

HasPtr f(const HasPtr &hp) 		// HasPtr passed by value, so it is copied
{	
	cout << "function f" << endl;
	cout << "HasPtr ret" << endl;
	HasPtr ret;
	cout << "ret = hp" << endl;
	ret = hp;        		// assignment copies the given HasPtr
							// proces ret
	cout << "function end" << endl;
	return ret;      		// ret and hp are destroyed
}

void HasPtr::show()
{
	cout << "h.use: " << *use << "  ";
}

int main()
{ 	
	cout << "h(\"hi mom!\")" << endl;
	HasPtr h("hi mom!"), h3;
	cout << "HasPtr h2 = h" << endl;
	HasPtr h2 = h;  		// no new memory is allocated, 
	                		// h and h2 share the same underlying string
	cout << "h2 = h" << endl;
	h3 = h2;
	cout << "HasPtr h4(h2)" << endl;
	HasPtr h4(h2), h5;  
	cout << "h5 = f(h);" << endl;
	h.print();
	h5 = f(h);
	//h.print();
	h5.print();
	cout << "end main" << endl; 
} 

