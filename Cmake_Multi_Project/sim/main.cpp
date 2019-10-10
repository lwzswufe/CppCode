#include <iostream>
using std::cout; using std::endl;
#include <stdio.h>
#include "data_struct.h"

int main()
{   
    unsigned sz = 5;
    DataManager* dm = create_datamanager(sz);
    printf("ceate new data size:%d, unit:%lu, dm:%p\n", 
            sz, sizeof(int), dm);
    cout << "create over " << endl;
    for (int i=0; i<sz; i++)
        append(dm, &i);
#ifdef __SIM__
    cout << "  define __SIM__" << endl;
#else 
    cout << "nodefine __SIM__" << endl;
#endif
    cout << __FILE__ << " end" << endl;
    return 0;
}
