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
    LogInfo* arr;
    // 队列写入数
    std::atomic<size_t> push_n;
    // 队列读取数
    std::atomic<size_t> pop_n;
};
// 队列数量
const static size_t QUEUE_NUM{2};
// 切换队列的提前量
static size_t SWITCH_ADVANCE{10};
// 当前使用一个队列
static LogQueue* CURRENT_QUEUE{nullptr};
// 当前使用一个队列
static LogQueue* BACKUP_QUEUE{nullptr};
// 队列数组
static LogQueue* QueueArr[QUEUE_NUM];
// 是否写出备选信息
static std::atomic<bool> EXTEND_BACKUP{false};
// 是否写出备选信息
static std::atomic<bool> SWITCHED{false};


static void Dealloc(LogQueue* queue)
{
    if (queue->arr != nullptr)
    {
        delete[] queue->arr;
    }
    queue->arr = nullptr;
};

static bool Alloc(LogQueue* queue)
{
    if (queue->arr != nullptr)
    {
       printf("error in alloc because queue:%p's string is not null\n", queue);
       return false;
    }
    queue->arr = new LogInfo[queue->capacity];
    memset(queue->arr, 0, sizeof(LogInfo) * queue->capacity);
    return true;
};

void LogQueueInitial(size_t _size, size_t advance)
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
        QueueArr[i]->length = sizeof(LogInfo);
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
    SWITCH_ADVANCE = advance;
    printf("Current:%p Backup:%p Advance:%lu\n", CURRENT_QUEUE, BACKUP_QUEUE, SWITCH_ADVANCE);
};

// 获取指定队列当前储存日志数量 
static size_t Size(const LogQueue* queue)
{
    return queue->push_n - queue->pop_n;
};

static void SwitchQueue()
{   
    // 切换队列
    printf("Switch BackupQueue push:%lu pop:%lu And CurrentQueue push:%lu pop:%lu \n", 
            size_t(BACKUP_QUEUE->push_n), size_t(BACKUP_QUEUE->pop_n), 
            size_t(CURRENT_QUEUE->push_n), size_t(CURRENT_QUEUE->pop_n));
    // 交换当前日志队列与 备用日志队列
    LogQueue* temp = CURRENT_QUEUE;
    CURRENT_QUEUE = BACKUP_QUEUE;
    BACKUP_QUEUE = temp;
    // 准备清空备用队列并扩展备用队列
    EXTEND_BACKUP = true;
}

LogInfo* GetBlankString(char log_level)
{   
    LogQueue* queue = CURRENT_QUEUE;
    // 判断当前日志队列是否已满
    if (Size(CURRENT_QUEUE) + SWITCH_ADVANCE >= CURRENT_QUEUE->capacity)
    {   
        // 判断备用日志队列是否为空
        if (Size(CURRENT_QUEUE) > CURRENT_QUEUE->capacity)
        {   
            char s[128];
            sprintf(s, "BackupQueue push:%lu pop:%lu but CurrentQueue is full push:%lu pop:%lu \n", 
                    size_t(BACKUP_QUEUE->push_n), size_t(BACKUP_QUEUE->pop_n), 
                    size_t(CURRENT_QUEUE->push_n), size_t(CURRENT_QUEUE->pop_n));
            printf(s);
            throw runtime_error(s);
        }
        else if (Size(BACKUP_QUEUE) == 0)
        {   
            if (!SWITCHED)
            {   
                SWITCHED = true;
                SwitchQueue();
                SWITCHED = false;
            }
        }
    }

    size_t str_id = queue->push_n++ % queue->capacity;
    LogInfo* info = queue->arr + str_id;
    info->log_level = log_level;
    return info;

}

const LogInfo* GetWriteString()
{   
    LogQueue* queue;
    if (Size(BACKUP_QUEUE) == 0)
    {
        if (EXTEND_BACKUP)
        {
            // 对备用队列进行扩容
            Dealloc(BACKUP_QUEUE);
            BACKUP_QUEUE->capacity *= 2;
            Alloc(BACKUP_QUEUE);
            // 标注备用队列信息已写出
            EXTEND_BACKUP = false;
        }
        queue = CURRENT_QUEUE;
    }
    else
    {
        queue = BACKUP_QUEUE;
    }
    // printf("%p push:%lu pop:%lu\n", queue, (size_t)queue->push_n, (size_t)queue->pop_n);
    // 获取待写出信息
    if (queue->pop_n < queue->push_n)
    {   
        size_t idx = queue->pop_n % queue->capacity;
        if (queue->arr[idx].confirm)
        {   
            ++queue->pop_n;
            // printf("output %lu:%s", idx, queue->arr[idx]);
            return queue->arr + idx;
        }
        
    }
    return nullptr;
}

void ComfirmString(LogInfo* info)
{
    info->confirm = true;
}

void PrintQueue()
{
    char s[128];
    sprintf(s, "BackupQueue:%p push:%lu pop:%lu CurrentQueue:%p push:%lu pop:%lu \n", 
            BACKUP_QUEUE, size_t(BACKUP_QUEUE->push_n), size_t(BACKUP_QUEUE->pop_n), 
            CURRENT_QUEUE, size_t(CURRENT_QUEUE->push_n), size_t(CURRENT_QUEUE->pop_n));
    printf(s);
}