#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

#include "Screen.h"

int main()
{
	Screen myScreen(3, 5);
	// move the cursor to a given position, and set that character 
	myScreen.move(0, 4).set('#');
	myScreen.display(cout);
	cout << endl;

	Screen nextScreen(5, 7, 'X');
	nextScreen.move(3,4).set('#').display(cout);
	cout << "\n";
	nextScreen.display(cout);
	cout << endl;

	const Screen blank(3, 5);			// 注意 这里是const类型
	myScreen.set('#').display(cout);  	// calls nonconst version
	cout << endl;
	blank.display(cout);	            // calls const version
	cout << endl;

	cout << "clear Z:\n";				// 用Z 覆盖屏幕
	myScreen.clear('Z').display(cout); 
	cout << endl;

	myScreen.move(1,0);
	myScreen.set('#');
	myScreen.display(cout); 
	cout << endl;

	myScreen.clear('Z').display(cout); 
	cout << endl;

	cout << "get_copy:\n";
	myScreen.get_copy().set(1, 2, '#'); // 获得Myscreen的拷贝并修改
	myScreen.display(cout); 
	cout << endl;
	// if move returns Screen not Screen&
	Screen temp = myScreen.move(1,0);   // 获得Myscreen的拷贝 因为返回类型不是 引用
	//Screen &temp = myScreen.move(1,0); // 获得Myscreen的本体 因为返回类型是 引用
	temp.set('#'); 						// the contents inside myScreen would be unchanged
	myScreen.display(cout);				// Myscreen不会改变
	cout << endl;

	temp.display(cout);				// Myscreen不会改变
	cout << endl;
}
