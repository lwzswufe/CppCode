#include "LogQueue.h"
#include <exception>
using std::runtime_error;

struct LogQueue
{   
    // 日志长度
    size_t length;
    // 队列大小
    size_t capacity;
    // 日志信息数组储存地址
    char ** string_arr;
    // 日志信息储存地址
    char * string;
    // 队列写入数
    std::atomic<size_t> push_n;
    // 队列读取数
    std::atomic<size_t> pop_n;
};
// 队列数量
const static size_t QUEUE_NUM{2};
// 当前使用一个队列
static LogQueue* CURRENT_QUEUE{nullptr};
// 当前使用一个队列
static LogQueue* BACKUP_QUEUE{nullptr};
// 队列数组
static LogQueue* QueueArr[QUEUE_NUM];
// 是否写出备选信息
static std::atomic<bool> WRITE_BACKUP{false};


static void Dealloc(LogQueue* queue)
{
    if (queue->string_arr != nullptr)
    {
        delete[] queue->string;
        delete[] queue->string_arr;
    }
    queue->string_arr = nullptr;
};

static bool Alloc(LogQueue* queue)
{
    if (queue->string_arr != nullptr)
    {
       printf("error in alloc because queue:%p's string is not null\n", queue);
       return false;
    }
    queue->string_arr = new char*[queue->capacity];
    queue->string = new char[queue->capacity * queue->length];
    for (size_t i=0; i<queue->capacity; i++)
    {
        queue->string_arr[i] = queue->string + i * queue->length;
    }
    return true;
};

void LogQueueInitial(size_t _size, size_t length)
{   
    for (unsigned i=0; i<QUEUE_NUM; ++i)
    {   
        if (QueueArr[i] != nullptr)
        {
            printf("LogQueue[%d] Initial has Initialed\n", i);
        }
        QueueArr[i] = new LogQueue{0};
        Dealloc(QueueArr[i]);
        QueueArr[i]->capacity = _size;
        QueueArr[i]->length = length;
        if (Alloc(QueueArr[i]))
        {
            QueueArr[i]->push_n = 0;
            QueueArr[i]->pop_n = 0;
            printf("LogQueue[%u] Initial Over %p capacity:%lu length:%lu\n", i, QueueArr[i], QueueArr[i]->capacity, QueueArr[i]->length);
        }
        else
        {
            printf("LogQueue[%u] Initial Failed\n", i);
        }
    }
    CURRENT_QUEUE = QueueArr[0];
    BACKUP_QUEUE = QueueArr[1];
    printf("Current:%p Backup:%p\n", CURRENT_QUEUE, BACKUP_QUEUE);
};

// 获取指定队列当前储存日志数量 
static size_t Size(const LogQueue* queue)
{
    return queue->push_n - queue->pop_n;
};

char* GetBlankString(char log_level)
{   
    // 判断当前日志队列是否已满
    if (Size(CURRENT_QUEUE) >= CURRENT_QUEUE->capacity)
    {   
        // 判断备用日志队列是否为空
        if (Size(BACKUP_QUEUE) != 0)
        {   
            char s[128];
            sprintf(s, "BackupQueue is not empty push:%lu pop:%lu but CurrentQueue is full push:%lu pop:%lu \n", 
                    size_t(BACKUP_QUEUE->push_n), size_t(BACKUP_QUEUE->pop_n), 
                    size_t(CURRENT_QUEUE->push_n), size_t(CURRENT_QUEUE->pop_n));
            printf(s);
            throw runtime_error(s);
        }
        else
        {   
            WRITE_BACKUP = true;
            printf("Switch BackupQueue push:%lu pop:%lu And CurrentQueue push:%lu pop:%lu \n", 
                    size_t(BACKUP_QUEUE->push_n), size_t(BACKUP_QUEUE->pop_n), 
                    size_t(CURRENT_QUEUE->push_n), size_t(CURRENT_QUEUE->pop_n));
            // 交换当前日志队列与 备用日志队列
            LogQueue* temp = CURRENT_QUEUE;
            CURRENT_QUEUE = BACKUP_QUEUE;
            BACKUP_QUEUE = temp;
        }
    }

    size_t str_id = CURRENT_QUEUE->push_n++ % CURRENT_QUEUE->capacity;
    char * str = CURRENT_QUEUE->string_arr[str_id];
    memset(str, 0, CURRENT_QUEUE->length * sizeof(char));
    str[0] = log_level;
    return str + 1;

}

const char* GetWriteString()
{   
    LogQueue* queue;
    if (WRITE_BACKUP)
    {   
        if (Size(BACKUP_QUEUE) == 0)
        {   
            // 对备用队列进行扩容
            Dealloc(BACKUP_QUEUE);
            BACKUP_QUEUE->capacity *= 2;
            Alloc(BACKUP_QUEUE);
            // 标注备用队列信息已写出
            WRITE_BACKUP = false;
            queue = CURRENT_QUEUE;
        }
        else
            queue = BACKUP_QUEUE;
    }
    else
        queue = BACKUP_QUEUE;
    // printf("%p push:%lu pop:%lu\n", queue, (size_t)queue->push_n, (size_t)queue->pop_n);
    // 获取待写出信息
    if (queue->pop_n < queue->push_n)
    {   
        size_t idx = queue->pop_n % queue->capacity;
        if (queue->string_arr[idx][queue->length-1] == 127)
        {   
            ++queue->pop_n;
            // printf("output %lu:%s", idx, queue->string_arr[idx]);
            return queue->string_arr[idx];
        }
        
    }
    return nullptr;
}

void ComfirmString(char* log)
{
    log[CURRENT_QUEUE->length - 2] = 127;
    // int str_id = (log - 1 - CURRENT_QUEUE->string) / CURRENT_QUEUE->length;
    // printf("Confirm %04d:%s", str_id, log);
}