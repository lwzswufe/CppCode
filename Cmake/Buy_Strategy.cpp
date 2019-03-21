#include "Buy_Strategy.h"

void Buy_Strategy::init()
{
    this->code_vec = {"600000", "600010"};
}

void Buy_Strategy::run()
{
    ;
}

void Buy_Strategy::update(Stock_Data* data_ptr)
{
    for(auto code: this->code_vec)
    {
        if(data_ptr->code == code &&
           data_ptr->trade_pr - data_ptr->settlement > 3)
            printf("Buy code:%s", code.c_str());
    }
}