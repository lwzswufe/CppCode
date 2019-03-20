#include <stdio.h> 
#include <time.h> 
#include <sys/time.h>

void sysLocalTime() 
{   // 获取精确到秒的时间
    time_t             timesec; 
    struct tm         *p; 
    time(&timesec); 
    p = localtime(&timesec); 
       
    printf("%d-%02d-%02d %02d:%02d:%02d\n", 
           1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 
           p->tm_hour, p->tm_min, p->tm_sec); 
       
} 
   
void sysUsecTime() 
{   // 获取精确到毫秒的时间
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
       
    gettimeofday(&tv, &tz); 
    printf("tv_sec:%ld\n",tv.tv_sec); 
    printf("tv_usec:%ld\n",tv.tv_usec); 
    printf("tz_minuteswest:%d\n",tz.tz_minuteswest); 
    printf("tz_dsttime:%d\n",tz.tz_dsttime); 
       
    p = localtime(&tv.tv_sec); 
    printf("time_now:%d-%02d-%02d %02d:%02d:%02d.%06ld\n", 
           1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 
           p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec); 
} 
   
int main(void) 
{ 
    sysLocalTime(); 
    printf("============gettimeofday==============\n"); 
    sysUsecTime(); 
       
    return 0; 
}  