//数据管理结构体
struct DataManager
{   
    // 数据起始指针
    int *begin;         
    // 数据末尾指针
    int *end;           
    // 数据当前指针
    int *current;  
    // 当前可用空间尾部
    int *stroage_end;  
    // 数据单元大小
    int unit_size;    
};

DataManager* create_datamanager(unsigned size);

void append(DataManager* dm, int* new_data);

