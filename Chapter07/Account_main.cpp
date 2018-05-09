
#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

#include <cstdio>

#include "Account.h"

int main()
{   
    //Account::init_rate(0.03);
    Account acc_1(137);
    acc_1.deposit(113.25);
    acc_1.debit(97.5);
    acc_1.show();
    acc_1.accrued_interest();
    acc_1.show();

    return 0;
}