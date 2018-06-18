/*
*/ 

#include <ctime>
using std::time;

#include <cstdlib>
using std::rand;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;
using std::normal_distribution;

#include <iostream>
using std::cerr; using std::cout; using std::endl;

#include <vector>
using std::vector; 

#include <algorithm>
using std::max_element;

#include <cstddef>
using std::size_t;

int main()
{
	default_random_engine e;  		// generates random unsigned integers
	for (size_t i = 0; i < 10; ++i)	
		cout << e() << " ";		 	// e() "calls" the object to produce the next random number
	cout << endl;					// e() 生成下一个随机数

									// uniformly distributed from 0 to 9 inclusive
	uniform_int_distribution<unsigned> u(0,9); //0-9均匀分布
	default_random_engine e2;  		// 随机数引擎
	for (size_t i = 0; i < 10; ++i)
    	cout << u(e2) << " ";		// 随机分布函数 u 调用随机数引擎 e2 
	cout << endl;

	default_random_engine e3;  		// generates normally distributed doubles
	normal_distribution<> n(100, 15);  // 正态分布函数
	for (size_t i = 0; i < 10; ++i)
    	cout << n(e3) << " ";
	cout << endl;

	for (size_t i = 0; i < 10; ++i) // bad, but common way to generate random numbers in a given range
		cout << rand()%10 << " ";	// r will be a between 0 and 9, but randomness is compromised
	cout << endl;					// 等效的坏办法

	default_random_engine e4;		// uniformly distributed from 0 to 9 inclusive
	uniform_int_distribution<unsigned> u2(0,9);
	for (size_t i = 0; i < 10; ++i)	// 注意 这次的调用结果和第一次的调用结果一模一样
    	cout << u2(e4) << " ";
	cout << endl;

	default_random_engine e5(time(0));  // seeding the engine causes it to generate different numbers 
	for (size_t i = 0; i < 10; ++i)	// 设置随机种子
    	cout << u2(e5) << " ";		// 设置种子后 调用结果就不同了
	cout << endl;
    								// 随机范围
    uniform_int_distribution<short> us1;     // values from 0 to 32767
    uniform_int_distribution<short> us2(42); // values from 42 to 32767
    cout << "min: " << us1.min() << " max: " << us1.max() << endl;
    cout << "min: " << us2.min() << " max: " << us2.max() << endl;

    default_random_engine e6;
    cout << "min: " << e6.min() << " max: " << e6.max() << endl;

	return 0;
}
