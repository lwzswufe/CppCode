#include <memory>
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;
#include <string>
using std::string;
#include <cstddef>
using std::size_t;
#include <utility> 
using std::pair; using std::make_pair;
#include <algorithm>
using std::min;
#include <vector>
using std::vector;

struct Stock_Data
{   
    int trade_pr;
    int settlement;
    string code;
};
typedef struct Stock_Data* Data_Ptr;
struct Strategy
{   
public:
    virtual void init();
    virtual void run();
    virtual void update(Stock_Data* data_ptr);
    int timenum;
    string timestr;
};