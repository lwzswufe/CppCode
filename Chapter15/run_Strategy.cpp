#include "Buy_Strategy.h" 
#include "Sell_Strategy.h"

int main()
{
    Buy_Strategy buy_cls(1);
    Sell_Strategy sell_cls(1);

    vector<Stock_Data> quotation_vec = {{ 97, 98, "600000"}, 
                                        { 60, 50, "600010"}, 
                                        {103, 98, "600000"}, 
                                        { 59, 60, "600004"}};
    for (auto stock_data: quotation_vec)
    {
        buy_cls.update(&stock_data);
        sell_cls.update(&stock_data);
    }
    return 0;
}