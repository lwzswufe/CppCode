#include "StaticMember.h"

int main()
{   
    BarsData::show();
    BarsData bar_1;
    bar_1.add(5);
    BarsData::show();
    BarsData bar_2;
    bar_2.add(6);
    bar_1.add(7);
    BarsData::show();
    return 0;
}