#include <ctime>
using std::time; using std::time_t; using std::localtime; using std::tm;
#include <iostream>
using std::ostream; using std::cin; using std::cout; using std::endl;


struct tm SetDate(int year, int month, int day)
{
    struct tm date{0};
    date.tm_year = year-1900;
    date.tm_mon  = month-1;
    date.tm_mday = day;
    return date;
}

struct tm SetDateByDelta(struct tm date, int day_delta)
{
    time_t timestamp = mktime(&date);
    timestamp += day_delta * 86400;
    struct tm *p = localtime (&timestamp);
    return *p;
}

void print(const struct tm *p)
{
    char buffer [80];                               // 格式化字符串
    strftime (buffer, 80, "Now it's %Y-%m-%d Week:%w.", p);
    cout << buffer << endl;
}

int main()
{   
    struct tm date = SetDate(2020, 12, 1);
    print(&date);
    struct tm date2 = SetDateByDelta(date, -1);
    print(&date2);
    struct tm date3 = SetDateByDelta(date, 34);
    print(&date3);
}