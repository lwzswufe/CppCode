// 传值参数
#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

									// function that takes a reference to an int 
									// and sets the given object to zero
									// i is just another name for the object passed to reset
void reset(int &i)                  // 传递i的引用
{	                                // 这将会改变主程序i的值
    i = 0;                          // changes the value of the object to which i refers
	cout << " ref" << endl;
}

									// function that takes a pointer 
									// and sets the pointed-to value to zero
void reset(int *ip)
{                                    // 通过地址修改主程序变量的值
    *ip = 0;                         // changes the value of the object to which ip points
    ip = nullptr;                    // changes the local copy of ip; the argument is unchanged
	cout << " ptr" << endl;
}

void reset_0(int *ip, int *(&oldip)) // int *表示数据类型时int指针  &oldip表示时主程序变量的引用 返回oldip变量
{                                    // 通过地址修改主程序变量的值
    oldip = ip + 1;
	cout << oldip << endl;
	*ip = 0;                         // changes the value of the object to which ip points
    ip = nullptr;                    // changes the local copy of ip; the argument is unchanged
	cout << " return" << endl;
}

int main() 
{
	int j = 42;                      // 传引用 值会被主程序改变
	reset(j);                        // j is passed by reference; the value in j is changed
	cout << "j = " << j  << endl;    // prints j = 0

	j = 42;                          // restore the original value of j
	cout << "address0: " << &j;
	reset(&j);                       // 传指针 changes j but not the address of j
	cout << "j = "  << j             // prints j = 0 
	     << " address1: " << &j << endl;// prints j = 0 指针被修改

	j = 42;                          // restore the original value of j
	int *p = &j;
	cout << "address0: " << p;
	reset(p);                        // 传指针 changes object to which p points not the address in p
	cout << "j = "  << *p            // prints j = 0
		 << " address1: " << &j << endl;

	j = 42;                          // restore the original value of j
	p = &j;
	int *old_p = nullptr;
	reset_0(p, old_p);                        // 传指针 changes object to which p points not the address in p
	cout << "j = "  << *p            // prints j = 0
		 << " address0: " << p  
		 << " address1: " << old_p
		 << endl;

    return 0;
}
