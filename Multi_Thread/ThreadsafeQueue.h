#include <memory>
#include <mutex>

/*
线程安全细粒度锁队列
*/
template<typename T>
class ThreadsafeQueue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    // 头节点锁
    std::mutex head_mutex;
    // 头节点
    std::unique_ptr<node> head;
    // 尾节点锁
    std::mutex tail_mutex;
    // 尾节点
    node* tail;
    // 大小
    int _size{0};
    // 获取尾节点
    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }
    // 删除头节点
    std::unique_ptr<node> pop_head()
    {   
        // 阻塞锁定
        std::lock_guard<std::mutex> head_lock(head_mutex);
        // 判断空队列
        if(head.get()==get_tail())
        {
            return nullptr;
        }
        std::unique_ptr<node> old_head=std::move(head);
        head=std::move(old_head->next);
        --_size;
        return old_head;
    }
public:
    // 默认构造函数
    ThreadsafeQueue(): head(new node),tail(head.get()) {}
    // 禁止拷贝构造
    ThreadsafeQueue(const ThreadsafeQueue& other)=delete;
    // 禁止赋值构造
    ThreadsafeQueue& operator=(const ThreadsafeQueue& other)=delete;
    // 尝试删除
    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> old_head=pop_head();
        return old_head?old_head->data:std::shared_ptr<T>();
    }
    // 获取大小
    int size()
    {   
        return _size;
    }
    // 是否为空
    bool empty()
    {   
        // printf("%p %p\n", head.get(), get_tail());
        return head.get()==get_tail();
    }
    // 推入数据
    void push(T new_value)
    {   
        // 复制数据
        std::shared_ptr<T> new_data(
            std::make_shared<T>(std::move(new_value)));
        // 分配新节点
        std::unique_ptr<node> p(new node);
        node* const new_tail=p.get();
        // 开始锁定
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data=new_data;
        tail->next=std::move(p);
        tail=new_tail;
        ++_size;
    }
};
