#ifndef _STRATEGY_H_
#include "Strategy.h"
#define _STRATEGY_H_
#endif


struct Buy_Strategy
{   
    Buy_Strategy(int id_):id(id_){ init(); };
    void init();
    void run();
    void update(Stock_Data* data_ptr);
private:
    int id;
    vector<string> code_vec;
};