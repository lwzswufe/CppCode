/*
静态成员必须为字面值常量类型的constexpr。
所谓的constexpr，就是常量表达式，指值不会改变且在编译过程中就能得到计算结果的表达式
*/
#include <string>

#include <cstdio>

#include <iostream>
using std::cout; using std::endl;

struct Account                                // 类名
{   
    //constexpr double get_rate() {return 0.03;}
    const static int rate = 3;             // 利率 
    double Cash;
    int account_no;

    Account(int account_id): account_no{account_id}, Cash{0} 
    {}        

    void deposit(double);
    void debit(double);
    void accrued_interest();
    void show();
};                                          // end class 这里的分号不可省略

inline void Account::deposit(double rmb)
{
    Cash += rmb;
}

inline void Account::debit(double rmb)
{
    if  (rmb >= Cash)
        Cash -= rmb;
    else
        cout << "not sufficient funds" << endl;
}

inline void Account::accrued_interest()
{
    Cash += Cash * rate * 0.01;
}

inline void Account::show()
{   
    char char_ptr[30];
    sprintf(char_ptr, "Account: %d have %.4f rmb", account_no, Cash);
    cout << char_ptr << endl;
}