#include <memory>
#include <stdio.h>
#include <string.h>
#include <atomic>

struct LogInfo
{
    char log_level;
    char str[496];
    bool confirm;
    int info_id;
};
// 循环队列初始化
// size_t _size 初始队列大小
// size_t advance 切换队列提前量
void LogQueueInitial(size_t _size, size_t advance);

// 获取一个空白字符串 获取失败返回nullptr
LogInfo* GetBlankString(char log_level);

// 获取一个待写出的字符串 获取失败返回nullptr
const LogInfo* GetWriteString();

// 确认某个字符串写出完毕
void ComfirmString(LogInfo* info);

// 输出队列信息
void PrintQueue();
