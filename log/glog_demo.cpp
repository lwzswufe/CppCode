#include <glog/logging.h>

/*
g++ -std=c++11 glog_demo.cpp -o glog_demo.o -lglog -L/usr/local/lib
找不到库就声明路径
export LD_LIBRARY_PATH=/usr/local/lib
*/


void (WriteError)(const char* data, size_t size)
{
    LOG(ERROR) << data;
}

int main(int argn, const char** argv)
{
    google::InitGoogleLogging((const char*)argv[0]);
    // 指定文件名
    google::SetLogDestination (google::INFO, "user.log");
    // 设置日志最低输出级别
    // 日志等级划分为GLOG_INFO = 0, GLOG_WARNING = 1, GLOG_ERROR = 2, GLOG_FATAL = 3
    FLAGS_minloglevel = google::INFO;
    // 文件名里使用自己定义时间戳 废弃默认的
    FLAGS_timestamp_in_logfile_name = false;
    // 指定日志目录
    FLAGS_log_dir = ".";
    // 每10次输出
    LOG_EVERY_N(INFO, 10) << "Got the " << google::COUNTER << "th cookie";
    // 条件日志记录
    int num_cookies = 11;
    LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
    // 输出错误
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(&WriteError);
    // 内存溢出
    char s[3];
    int a{237128179};
    memcpy(s, &a, sizeof(int));
    printf("%s", s);
    return 0;
}