#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct OrderBook
{
    char code[7];
    char market;
    int buy_price;
    int buy_vol;
    int sell_price;
    int sell_vol;
};
typedef struct OrderBook OrderBook;

// 从一行字符串里读取数据
bool get_data_from_string(OrderBook* ptr, char* line)
{
    if (strlen(line) < 10)
        return false;
    strncpy(ptr->code, line, 6);
    ptr->code[6] = 0;
    int market;
    int ret = sscanf(line + 5, "%d%d%d%d%d",
              &market, &(ptr->buy_price), &(ptr->buy_vol), &(ptr->sell_price), &(ptr->sell_vol));
    ptr->market = market;
    if ( ret != 5 )
        return false;
    else
        return true;
}

// 输出数据到stdout
int print_data(OrderBook * ptr)
{
    printf("Code:%s market:%d buy_price:%d buy_vol:%d sell_price:%d sell_vol:%d\n",
    ptr->code, ptr->market, ptr->buy_price, ptr->buy_vol, ptr->sell_price, ptr->sell_vol);
}

// 从txt读取数据
int read_data(const char* filename, OrderBook **data_arr)          // C语言风格
{   
    FILE * pFile;
    int arr_size = 0;
    size_t buffer_size = 1024;
    char buffer [buffer_size];
    OrderBook *new_data = (OrderBook *)malloc(sizeof(OrderBook));
    pFile = fopen(filename , "r");
    if (pFile == NULL) 
    {   
        char s[256];
        sprintf(s, "Error opening file %s", filename);
        perror (s);   // 输出异常
    }
    else
    {
        while ( !feof(pFile) )
        {
            if ( fgets(buffer , buffer_size , pFile) == NULL ) 
                break;
            if ( get_data_from_string( new_data, buffer) )
            {   
                data_arr[arr_size] = new_data;
                arr_size++;
                new_data = (OrderBook *)malloc(sizeof(OrderBook));
            }
        }
        fclose (pFile);
   }
   free(new_data); 
   return arr_size;
}

// 向指定内存写入数据
void* data2void(void *msg, int arr_size, OrderBook ** data_arr)
{
    void * tmp = msg;
    *(int*)tmp = arr_size;
    tmp += sizeof(int);
    for (int i=0; i<arr_size; i++)
    {
        memcpy(tmp, data_arr[i], sizeof(OrderBook));
        tmp += sizeof(OrderBook);
    }
    return msg;
}

// 从内存读取数据
void void2data(void *tmp, int * arr_size_ptr, OrderBook *** data_arr_ptr)
{
    int arr_size = *(int*)tmp;
    *arr_size_ptr = arr_size;
    tmp += sizeof(int);
    printf("arr_size:%d\n", arr_size);
    OrderBook ** data_arr = malloc(arr_size * sizeof(OrderBook*));
    OrderBook * data_ptr;
    *data_arr_ptr = data_arr;
    for (int i=0; i<arr_size; i++)
    {   
        data_ptr = malloc(sizeof(OrderBook));
        data_arr[i] = data_ptr;
        memcpy(data_ptr, tmp, sizeof(OrderBook));
        tmp += sizeof(OrderBook);
    }
}

int main()
{      
    char filename[128] = "data.txt";
    int arr_size, arr_size_void;
    OrderBook **data_arr, **data_arr_void = NULL;

    data_arr = malloc(100 * sizeof(OrderBook *)); // 预分配100个地址
    arr_size = read_data(filename, data_arr);

    for (int i=0; i<arr_size; i++)
        print_data(data_arr[i]);

    void * tcp_msg = malloc(sizeof(int) + arr_size * sizeof(OrderBook));
    data2void(tcp_msg, arr_size, data_arr);
    void2data(tcp_msg, &arr_size_void, &data_arr_void);
    for (int i=0; i<arr_size_void; i++)
        print_data(data_arr_void[i]);

    return 0;
}