#include<string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
#include <vector>
using std::vector;
#include <tuple>
using std::tuple; using std::make_tuple;
#include <cstring>
using std::sprintf;
#include <set>
using std::set;

namespace Data
{
    vector<string> code_vec {"000001", "000004", "000006"};
    vector<double> trade_pr {5.20, 1.75, 1.23};
    vector<double> up_limit {5.23, 1.70, 1.60};

    set<string> buy_codes;
    tuple<string, double, int> order;

    string buy_code;
    double buy_price;
    int buy_vol;

    string parse_tuple(tuple<string, double, int> order_)
    {
        buy_code  = std::get<0>(order_);      		// returns the 1st member of item
        buy_price = std::get<1>(order_);       		// returns the 2nd member of item
        buy_vol   = std::get<2>(order_); 			// returns the 3rd member of item
        char s[60];
        sprintf(s, "code: %s price:%.2f vol:%d", buy_code.data(), buy_price, buy_vol);
        order = make_tuple("blank", 0.00, 0);
        buy_codes.insert(buy_code);
        string str = s;
        return str;
    }
}