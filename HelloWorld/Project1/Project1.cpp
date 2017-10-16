// Project1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<ctime>
#include <iostream>
#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <cstdlib>

using namespace std;

long getTime()
{
	time_t now_time;
	now_time = time(NULL);
	cout << now_time;
	return now_time;
}

string getTimestr()
{
	system("pause"); //设置字符集 这一行需要写在函数里
	system("chap 65001");  //设置控制台为utf-8编码
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char timestr[200];
	printf("%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n",
		sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, 
		sys.wMilliseconds, sys.wDayOfWeek);

	sprintf_s(timestr, "%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n",
		sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond,
		sys.wMilliseconds, sys.wDayOfWeek);

	string s;
	s = timestr;
	return s;
}

int main()
{
	system("chcp 65001"); //设置字符集
	std::cout << "Hello World" << std::endl;
	long   timeint = getTime();
	cout << timeint << endl;
	string timestr = getTimestr();
	cout << timestr << endl;
	printf("请任意输入一个值 ....");
	int vi = 1;
	cin >> vi;
	return 0;
}

