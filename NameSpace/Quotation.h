#ifndef _DATA_H  
#include "Data.h"
#define _DATA_H
#endif
// 引入 namespace Data
struct quotation
{
    void get_quotation();
};

inline void quotation::get_quotation()
{
    int code_num = Data::code_vec.size(); 
    for (int i=0; i<code_num; i++)
    {
        Data::trade_pr[i] += 0.01;
    }
}