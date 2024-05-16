#include<stdio.h>
#include<time.h>
#include <iostream>
using std::cout; using std::endl; 
int main()
{
    struct timespec now, start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    const int count{1000000};
    for (int i=0; i<count; i++)
    {
        clock_gettime(CLOCK_REALTIME, &now);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    int used_sec = end.tv_sec- start.tv_sec;
    int used_ns = end.tv_nsec - start.tv_nsec;
    if (used_ns < 0)
    {
        used_ns += 1000000000;
        used_sec--;
    }
    double avg = ((double)used_sec * 1000000000 + used_ns ) / (double)count;
    tm* now_tm = localtime(&end.tv_sec);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);
    printf("Seconds = %ld \t Nanoseconds = %ld avg=%.3lf ns\n", used_sec, used_ns, avg);
    printf("current:%s.%09d\n", buffer, end.tv_nsec);
    return 0;
}