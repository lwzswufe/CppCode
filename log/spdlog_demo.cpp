#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
/*
g++ -std=c++11 spdlog_demo.cpp -o spdlog_demo.out
*/

int main() 
{
    // 开启并创建本地日志
    auto my_logger = spdlog::basic_logger_mt("logger name", "basic-log.txt");
    // change log pattern
    // 格式说明 https://spdlog.docsforge.com/v1.x/3.custom-formatting/#pattern-flags
    my_logger->set_pattern("[%H:%M:%S.%f] [%l] [thread %t %@] %v");
    // Set global log level to debug
    my_logger->set_level(spdlog::level::trace);

    my_logger->info("Welcome to spdlog!");
    my_logger->error("Some error message with arg: {}", 1);
    my_logger->warn("Easy padding in numbers like {:08d}", 12);
    my_logger->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    my_logger->info("Support for floats {:03.2f}", 1.23456);
    my_logger->info("Positional args are {1} {0}..", "too", "supported");
    my_logger->info("{:<30}", "left aligned");
    my_logger->debug("This message should be displayed..");    
    

    
    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");
}