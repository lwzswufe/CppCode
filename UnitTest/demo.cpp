#include<gtest/gtest.h>


/*
g++ -std=c++11 -o demo.out demo.cpp -lgtest -lpthread
*/

//  用户函数
int add(int a,int b)
{
    return a+b;
}

// 单元测试
TEST(testCase, test0)
{   
    // 相等
    EXPECT_EQ(add(2, 3), 5);
    // 大于等于
    EXPECT_GE(add(2, 3), 4);
    // 小于ss
    EXPECT_LT(add(2, 3), 5);
}

// 程序入口
int main(int argc,char **argv)
{
  // 传递命令行参数
  testing::InitGoogleTest(&argc,argv);
  // 自动运行所有测试
  return RUN_ALL_TESTS();
}