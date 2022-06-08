#include <glog/logging.h>

/*
g++ -std=c++11 glog_demo.cpp -o glog_demo.o -lglog -L/usr/local/lib
找不到库就声明路径
export LD_LIBRARY_PATH=/usr/local/lib
*/


int main(int argn, const char** argv)
{
    google::InitGoogleLogging((const char*)argv[0]);
    // 指定文件名
    google::SetLogDestination (google::INFO, "user.log");
    // 文件名里使用自己定义时间戳 废弃默认的
    FLAGS_timestamp_in_logfile_name = false;
    // 指定日志目录
    FLAGS_log_dir = ".";
    // 每10次输出
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    // 条件日志记录
    int num_cookies = 11;
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
}