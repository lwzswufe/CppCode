#ifndef _DATA_H
#include "Data.h"
#define _DATA_H
#endif

#include "strategy.h"
#include "Quotation.h"

int main()
{
    strategy  s_cls;
    quotation q_cls;
    bool is_trade;
    
    for (int i=0; i<10; i++)
    {
        q_cls.get_quotation();
        is_trade = s_cls.run();
        if (is_trade)
        {
            cout << Data::parse_tuple(Data::order) << endl;
        }
    }
}