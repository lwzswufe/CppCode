#include <iostream>
using std::cout; using std::endl; 

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::duration;                    // 时间段
using std::chrono::system_clock;                // 系统时间
using std::chrono::duration_cast;               // 时间类型转换
using std::chrono::seconds;                     // 秒
using std::chrono::microseconds;                // 毫秒
using std::chrono::milliseconds;                // 微秒
using std::chrono::nanoseconds;                 // 纳秒

int main()
{
    steady_clock::time_point time_st = steady_clock::now();
                                                // 硬件时间
    system_clock::time_point time_st_system_ = system_clock::now();  
                                                // 系统时间
    const int cycle{1000000};
    for (int i=0; i<cycle; i++)
    {
        // steady_clock::time_point clock = steady_clock::now();
        system_clock::time_point clock = std::chrono::high_resolution_clock::now();
        // clock = system_clock::now(); 
    }

    steady_clock::time_point time_ed = steady_clock::now();
    system_clock::time_point time_ed_system_ = system_clock::now();

    steady_clock::duration d1 = time_ed - time_st;
    steady_clock::duration d2 = time_ed.time_since_epoch() - time_st.time_since_epoch();
                                                // time_clock.time_since_epoch() 记时点到现在的时间
    system_clock::duration d3 = time_ed_system_ - time_st_system_;

    duration<int64_t, std::micro> d_us {7};     // 定义周期类型 duration
    duration<int64_t, std::milli> d_ms {8};     // 

    cout << d_us.count() << "us" << endl;
    cout << d_ms.count() << "ms" << endl;
    d_us += d_ms;
    cout << d_us.count() << "us" << endl;
    //duration_cast<TimeType>(d)  时间类型转换

    cout << "program used clock cycle(ns): " << d1.count() << endl;
    cout << "program used clock cycle(ns): " << d2.count() << endl;
    cout << "program used clock cycle(ns): " << d3.count() << endl;
    cout << "program average used clock cycle(ns): " << d3.count() / cycle << endl;
    
    cout << "program used clock cycle(us): " << duration_cast<microseconds>(d1).count() << endl;
    cout << "program used clock cycle(ms): " << duration_cast<milliseconds>(d1).count() << endl;
    cout << "program used clock cycle(s) : " << duration_cast<seconds>(d1).count() << endl;

    system_clock::time_point now = system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&time) << std::endl;
    return 0;
}