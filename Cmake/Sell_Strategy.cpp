#include "Sell_Strategy.h"

void Sell_Strategy::init()
{
    this->position_vec = {{"600000", 100}, {"600004", 54}};
}

void Sell_Strategy::run()
{
    ;
}

void Sell_Strategy::update(Stock_Data* data_ptr)
{
    for(auto position: this->position_vec)
    {
        if(data_ptr->code == position.first &&
           data_ptr->trade_pr - position.second > 5)
            printf("sell code:%s", position.first.c_str());
    }
}