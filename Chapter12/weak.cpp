/*
*/ 
#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

#include <memory>
using std::make_shared; using std::weak_ptr; using std::shared_ptr;

#define print(x) cout << #x << ": " << x << endl; 

int main()
{
	shared_ptr<int> p = make_shared<int>(42);
	shared_ptr<int> p1 = make_shared<int>();

	print(p.use_count());

	weak_ptr<int> wp(p); 					// wp weakly shares with p; use count in p is unchanged 

	print(p.use_count());					// 不增加shared_ptr计数

	if (shared_ptr<int> np = wp.lock())  	// true if np is not null
		cout << "wp point:" << *np << endl;
	else
		cout << "wp point null" << endl;

	p1 = p;

	print(wp.use_count());

	p.reset(); 

	print(wp.use_count());					// 释放对象急会减少 shared_ptr计数

	if (shared_ptr<int> np = wp.lock())  	// true if np is not null
		cout << "wp point:" << *np << endl;
	else
		cout << "wp point null" << endl;

	print(*p1);
}
