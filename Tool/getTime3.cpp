#include<ctime>
#include<iostream>
#include<windows.h> 
#include<stdio.h> 

using namespace std;

double getCurrentTime()
{   
    struct timeval tv;    
    mingw_gettimeofday(&tv, NULL);    
    return tv.tv_sec % 3600 + tv.tv_usec / 1000.0;  
}

string getCurrentTimeStr()
{   
    struct timeval tv;    
    mingw_gettimeofday(&tv, NULL);   
    char s[64];
    long seconds = tv.tv_sec % 86400;
    //cout << seconds << ", " << tv.tv_usec << endl;
    sprintf_s(s, "%02d:%02d:%02d.%03d", 8 + seconds / 3600, seconds / 60 % 60, seconds % 60, tv.tv_usec / 1000);
    return s;  
}

int main()
{
	double d = getCurrentTime();
    string s = getCurrentTimeStr();
	cout << "seconds" << d << endl;
    cout << s << endl;
	return 0;
}