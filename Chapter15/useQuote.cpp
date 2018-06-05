#include "Quote.h"

#include <algorithm>
using std::min;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::ostream; using std::endl; 
using std::cout;

int main()
{
	Quote base("0-201-82470-1", 50);
	print_total(cout, base, 10);        // calls Quote::net_price     
    
    // Disc_quote disc("0-201-82470-1", 50, 5, .19);
                                        // 我们不能直接创建一个抽象基类的对象
	Bulk_quote derived("0-201-82470-1", 50, 5, .19);
	print_total(cout, derived, 10);     // calls Bulk_quote::net_price 重载
	
	Quote *baseP = &derived;            // 父类指针可以指向子类的地址
    //Bulk_quote *derivedP = &base;     // 子类指针不可以指向父类的地址

	double undiscounted = baseP->Quote::net_price(42);
                                        // 子类调用父类方法
    cout << "undiscounted: " << undiscounted << endl;
    double discounted = baseP->net_price(42);
    cout << "discounted: " << discounted << endl;

    //Bulk_quote derived_b = base;      // 不存在父类->子类的隐式转换
    Quote bulk_copy = derived;          // 存在子类->父类的隐式转换
    print_total(cout, bulk_copy, 10);   

    //Bulk_quote bulk_2();              // 由于实际上无法访问父类私有属性 造成初始化失败 
    //print_total(cout, bulk_2, 10);
}