#include "data_struct.h"
#include <string.h>
#ifdef __SIM__
#include<stdio.h>
#endif 

DataManager* create_datamanager(unsigned size)
{
    int* begin = new int[size];
    int* end = begin + size;
    memset(begin, 0, size * sizeof(int));
    DataManager* dm = new DataManager{begin, begin, begin, end, sizeof(int)};
#ifdef __SIM__
    printf("ceate new data size:%d, unit:%lu, dm:%p begin:%p\n", 
            size, sizeof(int), dm, dm->current);
#endif 
    return dm;
}

void append(DataManager* dm, int* new_data)
{   
    if (dm == NULL || dm->current == NULL)
        return;
    if (dm->current != dm->stroage_end)
    {
        *(dm->current) = *new_data;
#ifdef __SIM__
        printf("add new data:%d, current:%p stroage_end:%p\n", 
                *(dm->current), dm->current, dm->stroage_end);
#endif
        dm->current++;
    }
}