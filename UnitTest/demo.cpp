#include<gtest/gtest.h>
#include<algorithm>
#include<stdio.h>


/*
g++ -std=c++11 -o demo.out demo.cpp -lgtest -lpthread
*/

//  用户函数
int add(int a,int b)
{
    return a+b;
}

// TestFunAdd 用户自定义测试名称
// test001  用户自定义用例名称
// 单元测试
TEST(TestFunAdd, test001)
{   
    // 相等
    EXPECT_EQ(add(2, 3), 5);
    // 大于等于
    EXPECT_GE(add(2, 3), 4);
    // 小于ss
    EXPECT_LT(add(2, 3), 5);
}

// 复杂对象的单元测试
// 队列类
class Queue
{
public:
    Queue();
    ~Queue();
    void push(int a);
    int pop();
    int size();
private:
    void alloc(int size);
    int _size{0};
    int _capacity{0};
    int *_arr{nullptr};
    int *_begin{nullptr};
    int *_end{nullptr};
};

Queue::Queue() {}

Queue::~Queue()
{
    if (_arr != nullptr)
        delete[] _arr;
}
void Queue::push(int a)
{   
    // 检查容量 最大容量 _capacity - 1
    if (_size + 2 > _capacity)
    {   
        alloc(std::max(2, _capacity * 2));
    }
    *_end = a;
    ++_end;
    ++_size;
    // 越界判断
    if (_end >= _arr + _capacity)
    {
        _end = _arr;
    }
}

int Queue::pop()
{
    // 检查容量
    if (_size <= 0)
    {
        return 0;
    }
    --_size;
    int r = *_begin;
    ++_begin;
    // 越界判断
    if (_begin >= _arr + _capacity)
    {
        _begin = _arr;
    }
    return r;
}

void Queue::alloc(int size)
{   
    // 分配新内存
    int *new_arr = new int[size];
    if(_size > 0)
    {   
        // 拷贝旧内存
        if (_end > _begin)
        {
            memcpy(new_arr, _begin, _size * sizeof(int));
            // printf("copy data from %p -> %p %d -> %d _size:%d/%d ",
            //        _begin, new_arr, _begin[0], new_arr[0], _size, _capacity);
        }
        else 
        {   
            int copy_num = _arr + _capacity - _begin;
            memcpy(new_arr, _begin, copy_num * sizeof(int));
            memcpy(new_arr + copy_num, _arr, (_end - _arr) * sizeof(int));
        }
        // 释放旧内存
        delete[] _arr;
    }
    // 初始化
    _arr = new_arr;
    _capacity = size;
    _begin = _arr;
    _end = _arr + _size;
    // 越界判断
    if (_end >= _arr + _capacity)
    {
        _end = _arr;
    }
    // printf("size:%d\n", size);
}

// 返回容量
int Queue::size()
{
    if (_end >= _begin)
    {
        return _end - _begin;
    }
    else
    {
        return _capacity + (_end -  _begin);
    } 
}

class Queue_Test : public ::testing::Test 
{
protected:
    // 测试初始化函数 测试前运行
    void SetUp() override 
    {
        queue_1.push(1);
        queue_1.push(2);
    }
    // 测试清理函数 测试后运行
    void TearDown() override 
    {
        ;
    }
    // 测试对象1
    Queue queue_1;
    // 测试对象2
    Queue queue_2;
};

// 单元测试 1
// TEST_F提供了一个初始化函数（SetUp）和一个清理函数(TearDown)
// Queue_Test 用户自定义测试类 需要定义
// test001  用户自定义用例名称
TEST_F(Queue_Test, test_pop001)
{   
    // 相等
    EXPECT_EQ(queue_1.pop(), 1);
    queue_1.push(3);
    EXPECT_EQ(queue_1.pop(), 2);
    EXPECT_EQ(queue_1.size(), 1);
    EXPECT_EQ(queue_1.pop(), 3);
    EXPECT_EQ(queue_1.size(), 0);
    EXPECT_EQ(queue_1.pop(), 0);
    // 相等
    EXPECT_EQ(queue_2.pop(), 0);
    const int size{130};
    for (int i=1; i<=size; ++i)
        queue_2.push(i);
    // 验证相等，不相等就返回
    ASSERT_EQ(queue_2.size(), size);
    for (int i=1; i<=size; ++i)
    {   
        ASSERT_EQ(queue_2.pop(), i);
    }
}

// 单元测试 2
TEST_F(Queue_Test, test_push001)
{   
    // 相等
    EXPECT_EQ(queue_1.size(), 2);
    queue_1.push(3);
    EXPECT_EQ(queue_1.size(), 3);
    queue_1.push(4);
    EXPECT_EQ(queue_1.size(), 4);
    // 相等
    EXPECT_EQ(queue_2.size(), 0);
    queue_2.push(1);
    EXPECT_EQ(queue_2.size(), 1);
}

// 程序入口
int main(int argc,char **argv)
{
  // 传递命令行参数
  testing::InitGoogleTest(&argc,argv);
  // 自动运行所有测试
  return RUN_ALL_TESTS();
}