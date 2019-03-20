#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

double getTime_0(double time_)
{   // hhmmss 时间转化为日内时间戳
    int h = time_ / 10000;
    int m = time_ / 100;
    return time_ - h * 2400 - m * 40;
}

double getTime_1(double time_)
{   // 日内时间戳转化为hhmmss时间
    int h = time_ / 3600;
    int m = time_ / 60;
    return time_ + h * 4000 + m * 40;
}

int main()
{
    double t = 94603.3;
    cout << t << ", "
         << getTime_0(t) << ", "
         << getTime_1(getTime_0(t)) << endl;
}