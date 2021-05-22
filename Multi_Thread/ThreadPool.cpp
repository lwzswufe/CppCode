#include <atomic>
#include <thread>
#include <pthread.h>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <time.h> 
#include <unistd.h>
#include <sys/time.h>


/*
g++ -std=c++11 ThreadPool.cpp -o ThreadPool.out -lpthread 
*/
// 线程安全队列
template <typename T>
class safe_queue
{
public:
    bool empty();
    size_t size();
    void push_back(T);
    T pop_front();
    bool try_pop(T&);
private:
    std::mutex _m;
    std::queue<T> _q{};
};

// 任务结构体
struct task_data
{   // 函数对象类型 返回void 输入 int
    std::function<void(int)> fun;
    // 函数参数
    int task_id;
};

class thread_pool
{
private:
    // 任务完成标致
    std::atomic_bool done;
    // 任务队列
    safe_queue<task_data> work_queue;
    // 线程数组
    std::vector<std::thread> threads;
    // 执行任务
    void worker_thread(unsigned thread_id);
public:
    // 构造函数 
    thread_pool();
    // 析构函数
    ~thread_pool();
    // 子线程回收函数
    void join();
    // 提交任务
    // template<typename FunctionType>
    void submit(task_data __ino_t_defined);
};

void thread_pool::worker_thread(unsigned thread_id)
{   
    printf("worker_thread %u start done:%d\n", thread_id, done.load());
    while(!done)
    {
        task_data td;
        if(work_queue.try_pop(td))
        {   
            printf("get task id:%d\n", td.task_id);
            td.fun(td.task_id);
        }
        else
        {
            std::this_thread::yield();
        }
    }
    printf("worker_thread %u end\n", thread_id);
}

// template<typename FunctionType>
void thread_pool::submit(task_data td)
{   
    work_queue.push_back(td);
    printf("submit task:%d\n", td.task_id);
}

thread_pool::~thread_pool()
{
    done=true;
}

thread_pool::thread_pool()
{   
    done = false;
    // joiner(threads)
    unsigned const thread_count=std::thread::hardware_concurrency();
    try
    {
        for(unsigned i=0;i<thread_count;++i)
        {
            threads.push_back(
                std::thread(&thread_pool::worker_thread, this, i));
            printf(" start thread:%u\n", i);
        }
    }
    catch(...)
    {
        done=true;
        throw;
    }
};


void thread_pool::join()
{   
    while(!work_queue.empty())
    {
        usleep(1);
    }
    done = true;
    for (unsigned i=0; i<threads.size(); ++i)
    {
        threads[i].join();
    }
}


template<typename T>
bool safe_queue<T>::empty()
{
    return _q.empty();
}


template <typename T>
size_t safe_queue<T>::size()
{
    return _q.size();
}

template <typename T>
void safe_queue<T>::push_back(T t)
{   
    _m.lock();
    _q.push(t);
    _m.unlock();
}

template <typename T>
bool safe_queue<T>::try_pop(T& t)
{
    if (_m.try_lock())
    {   
        if (_q.empty())
        {
            _m.unlock();
            return false;
        }
        else 
        {
            t = _q.front(); 
            _q.pop();
            _m.unlock();
            return true;
        }
        
    }
    else
    {
        return false;
    }
}

void print_time() 
{   // 获取精确到毫秒的时间
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
       
    gettimeofday(&tv, &tz); 
    p = localtime(&tv.tv_sec); 
    printf("time_now:%d-%02d-%02d %02d:%02d:%02d.%06ld\n", 
           1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 
           p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec); 
} 

void task(int task_id)
{   
    usleep(task_id);
    printf("task_id:%d ", task_id);
    print_time();
}

int main()
{   
    thread_pool tp;
    for (int i = 1; i < 50; ++i)
    {   
        task_data td;
        td.fun = task;
        td.task_id = i;
        tp.submit(td);
    }
    tp.join();
    return 0;
}