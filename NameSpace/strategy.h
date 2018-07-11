#ifndef _DATA_H
#include "Data.h"
#define _DATA_H
#endif

// 引入 namespace Data

struct strategy
{
    bool run();
};

inline bool strategy::run()
{
    int code_num = Data::code_vec.size(); 
    for (int i=0; i<code_num; i++)
    {  
        if (Data::trade_pr[i] >= Data::up_limit[i] and 
            Data::buy_codes.count(Data::code_vec[i]) == 0)
        {
            Data::order =  make_tuple(Data::code_vec[i], Data::up_limit[i], 100);
            return true;
        }
    }
    return false;
}