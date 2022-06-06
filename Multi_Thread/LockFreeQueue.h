#include <memory>
#include <atomic>

template<typename T>
class LockFreeQueue
{
private:
    // 节点
    struct node
    {
        std::shared_ptr<T> data;
        node* next;
        node():
            next(nullptr)
        {}
    };
    // 头节点
    std::atomic<node*> head;
    // 尾节点
    std::atomic<node*> tail;
    // 删除头节点
    node* pop_head()
    {
        node* const old_head=head.load();
        if(old_head==tail.load())
        {
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }
public:
    // 构造函数
    LockFreeQueue(): head(new node),tail(head.load()){}
    // 禁止拷贝构造
    LockFreeQueue(const LockFreeQueue& other)=delete;
    // 禁止赋值构造
    LockFreeQueue& operator=(const LockFreeQueue& other)=delete;
    // 析构
    ~LockFreeQueue()
    {
        while(node* const old_head=head.load())
        {
            head.store(old_head->next);
            delete old_head;
        }
    }
    // 获取并删除头节点数据
    std::shared_ptr<T> pop()
    {
        node* old_head=pop_head();
        if(!old_head)
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(old_head->data);
        delete old_head;
        return res;
    }
    // 在尾部添加数据
    void push(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(new_value));
        node* p=new node;
        node* const old_tail=tail.load();
        old_tail->data.swap(new_data);
        old_tail->next=p;
        tail.store(p);
    }
};