#include <iostream>
#include<windows.h>

using namespace std;

int main()
{   
    int b = 07;             // 表示8进制07  如输入09会报错
	int a = 0x16;           // 表示16进制16 即22
	double c = 10.;
	cout << b << a << c << endl;

	char d = 'a';           // char 单个字符 单引号
	cout << d << endl;

	string e = "lahf";     // 字符串  双引号  变量不要同名 会引发编译错误
	cout << e << endl;

	cout << '\115' << '\n' << '\a'; //\115转义字符  M的ascii码=115
	Beep(494, 200);         // 输出声音 需要#include<windows.h> Beep（频率，持续时间）；

	int f = {3};
	cout << f << endl;
	return 0;
}