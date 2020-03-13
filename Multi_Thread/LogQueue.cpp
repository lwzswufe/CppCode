#include "LogQueue.h"

static size_t CAPACITY = 0;
static size_t LENGTH = 0;
static char ** STRING_ARR = nullptr;
static char *  STRING = nullptr;
// 写入数
std::atomic<size_t> PUSH_N{0};
// 读取数
std::atomic<size_t> POP_N{0};

void static Dealloc()
{
    if (STRING_ARR != nullptr)
    {
        for (size_t i=0; i<CAPACITY; i++)
        {
            delete[] STRING_ARR[i];
        }
        delete[] STRING_ARR;
    }
    STRING_ARR = nullptr;
};

bool static Alloc()
{
    if (STRING_ARR != nullptr)
    {
       printf("error in alloc because STRING_ARR is not null\n");
       return false;
    }
    STRING_ARR = new char*[CAPACITY];
    STRING = new char[CAPACITY * LENGTH];
    for (size_t i=0; i<CAPACITY; i++)
    {
        STRING_ARR[i] = STRING + i * LENGTH;
    }
    return true;
};

void LogQueueInitial(size_t _size, size_t length)
{   
    Dealloc();
    CAPACITY = _size;
    LENGTH = length;
    if (Alloc())
    {
        PUSH_N = 0;
        POP_N = 0;
        printf("LogQueue Initial Over capacity:%lu length:%lu\n", CAPACITY, LENGTH);
    }
    else
        printf("LogQueue Initial Failed\n");
}

size_t static Size()
{
    return PUSH_N - POP_N;
}

char* GetBlankString(char log_level, size_t &str_id)
{
    if (Size() >= CAPACITY)
    {   
        // printf("Queue is full push:%lu pop:%lu\n", size_t(push_n), size_t(pop_n));
        return nullptr;
    }
    else
    {
        str_id = PUSH_N++ % CAPACITY;
        char * str = STRING_ARR[str_id];
        memset(str, 0, LENGTH * sizeof(char));
        str[0] = log_level;
        return str + 1;
    }
}

const char* GetWriteString()
{
    if (POP_N < PUSH_N)
    {   
        size_t idx = POP_N % CAPACITY;
        if (STRING_ARR[idx][LENGTH-1] == 127)
        {   
            ++POP_N;
            return STRING_ARR[idx];
        }
        
    }
    return nullptr;
}

void ComfirmString(size_t str_id)
{
    if (str_id < CAPACITY)
    {   
        STRING_ARR[str_id][LENGTH-2] = 0;
        STRING_ARR[str_id][LENGTH-1] = 127;
    }
}