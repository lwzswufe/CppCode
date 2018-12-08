#include<ctime>
#include<iostream>
#include<windows.h> 
#include<stdio.h> 

using namespace std;
double getCurrentTime()
{   
    double time_d;
    struct timeval tv;    
    mingw_gettimeofday(&tv,NULL);    
    return tv.tv_sec % 3600 + tv.tv_usec / 1000.0;  
}

int main()
{
	double d = getCurrentTime();
	cout << "seconds" << d << endl;
	return 0;
}