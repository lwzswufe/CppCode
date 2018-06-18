/*
*/ 

#include <cstddef>
using std::size_t;

#include <ctime>
using std::time;

#include <cstdlib>
using std::rand;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <iostream>
using std::cerr; using std::cout; using std::endl;

#include <vector>
using std::vector;

vector<unsigned> bad_randVec()
{
	default_random_engine e;    
	uniform_int_distribution<unsigned> u(0,9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
    	ret.push_back(u(e));
	return ret;
}

vector<unsigned> good_randVec()
{
	// because engines and distributions retain state, they usually should be
	// defined as static so that new numbers are generated on each call
	// 将随机生成器设置为静态变量 防止每一次生成的随机数都一样
	static default_random_engine e;    
	static uniform_int_distribution<unsigned> u(0,9);
	vector<unsigned> ret;
	for (size_t i = 0; i < 100; ++i)
    	ret.push_back(u(e));
	return ret;
}

int main()
{
	vector<unsigned> v1(bad_randVec());
	vector<unsigned> v2(bad_randVec());

	// will print equal
	cout << ((v1 == v2) ? "equal" : "not equal") << endl;

	// very unlikely to print equal
	if (good_randVec() == good_randVec())
		cout << "equal!" << endl;
	else
		cout << "not equal" << endl;
}
