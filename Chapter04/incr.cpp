// 递增和递减运算符 

#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <iterator>
using std::begin; using std::end;

int main() 
{
	int i = 0, j;
	j = ++i; // j = 1, i = 1: prefix yields the incremented value
	cout << "j = ++i i先+1 后赋值 " << i << " " << j << endl;

	j = i++; // j = 1, i = 2: postfix yields the unincremented value
	cout << "j = i++ i先赋值 后+1 " << i << " "  << j << endl;

	int arr[] = {0, 1, 2, 3};
	int *p = arr;                    // 这里使用arr 而非 *arr  因为 arr返回的就是第一个元素所在地址
	cout << p << ", " << &arr << " "  << endl;

	for (int *ptr = arr; ptr < &arr[4]; ptr++)  
		cout << *ptr++ << ", ";      // 先执行 ptr++ 再取地址
	cout << endl;

	for (int *ptr = arr; ptr < &arr[4];)
		cout << *ptr++ << ", ";     // 先执行 ptr++ 再取地址
	cout << endl;

	for (int *ptr = arr; ptr < &arr[4]; ++ptr)  
		cout << *ptr << ", ";     // 这里的 ++ptr 实际上等于 ptr++
	cout << endl;

	for (int *ptr = arr; ptr < &arr[4]; ptr++)
		cout << (*ptr)++ << ", ";   // 先取地址 在执行指针++
	cout << endl;

	char s[] = "vector";           // 末尾自带\0
	auto s_end = end(s);
	for(auto s_end = end(s)-1;s_end != begin(s); --s_end)
		cout << *(s_end - 1);
	cout << endl;

	return 0;
}
