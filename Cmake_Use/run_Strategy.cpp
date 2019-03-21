#include "Buy_Strategy.h" 
int main()
{
    Buy_Strategy buy_cls(1);
    Data_Ptr pdata;
    Stock_Data sd;
    vector<Stock_Data> quotation_vec = {{ 97, 98, "600000"}, 
                                        { 60, 50, "600010"}, 
                                        {103, 98, "600000"}, 
                                        { 59, 60, "600004"}};
    for (int i=0; i<quotation_vec.size(); i++)
    {   
        sd = quotation_vec[i];
        pdata = &sd;
        buy_cls.update(pdata);
    }
    return 0;
}