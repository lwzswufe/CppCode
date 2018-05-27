
#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;

#include <ctime>
using std::time; using std::time_t; using std::localtime; using std::tm;

int main()
{   
    time_t timenum;
    time(&timenum);                                 // 获取时间戳
    cout << timenum << endl;
    long timenum_int;
    time(&timenum);
    cout << timenum_int << endl;
    timenum_int = timenum;                          // 直接用int long类型接受时间戳 数据会异常 需要转化
    cout << timenum_int << endl;

    struct tm * timeinfo;
    time (&timenum);
    timeinfo = localtime (&timenum);
    printf ("Current local time and date: %s", asctime(timeinfo));

    char buffer [80];                               // 格式化字符串
    strftime (buffer, 80, "Now it's %Y-%m-%d.", timeinfo);
    cout << buffer << endl;

    cout << "sec: " << timeinfo->tm_sec << endl;
    cout << "min: " << timeinfo->tm_min << endl;
    cout << "hour:" << timeinfo->tm_hour << endl;
    cout << "day: " << timeinfo->tm_mday << endl;
    cout << "mon: " << timeinfo->tm_mon << endl;
    cout << "year:" << timeinfo->tm_year << endl;
    cout << "wday:" << timeinfo->tm_wday << endl;
    cout << "yday:" << timeinfo->tm_yday << endl;
}