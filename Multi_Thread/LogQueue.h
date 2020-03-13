#include <memory>
#include <stdio.h>
#include <string.h>
#include <atomic>
// 循环队列初始化
// size_t _size 队列大小
// size_t length 队列长度
void LogQueueInitial(size_t _size, size_t length);

// 获取一个空白字符串 获取失败返回nullptr
char* GetBlankString(char log_level, size_t &str_id);

// 获取一个待写出的字符串 获取失败返回nullptr
const char* GetWriteString();

// 确认某个字符串写出完毕
void ComfirmString(size_t str_id);

