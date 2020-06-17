#include <stdio.h>

#define TYPE_UNKNOWN    '0'
#define TYPE_INT        '1'
#define TYPE_DOUBLE     '2'
#define TYPE_STR        '3'

union Data
{
    int         i;
    double      d;
    char        str[8];
};

struct Named_Data
{
    char type;
    union Data data;
};

struct Anonymous_Data
{
    char type;
    union
    {
        int         i;
        double      d;
        char        str[8];
    };
};

void print_data(const struct Named_Data *nd)
{
    switch(nd->type)
    {
    case TYPE_INT: 
        printf("type int    i = %d\n", nd->data.i); break;
    case TYPE_DOUBLE:
        printf("type double d = %.4lf\n", nd->data.d); break;
    case TYPE_STR:
        printf("type str    s = %s\n", nd->data.str); break;
    default:
        printf("type unknown\n"); 
    }
}

void print_data(const struct Anonymous_Data* ad)
{
    switch(ad->type)
    {
    case TYPE_INT: 
        printf("type int    i = %d\n", ad->i); break;
    case TYPE_DOUBLE:
        printf("type double d = %.4lf\n", ad->d); break;
    case TYPE_STR:
        printf("type str    s = %s\n", ad->str); break;
    default:
        printf("type unknown\n"); 
    }
}

int main()
{   
    printf("联合\n");
    union Data i = {7},
               d = {.d=1.2},
               s = {.str="May"};
    printf("union int    i = %d\n", i.i);
    printf("union double d = %.4lf\n", d.d);
    printf("union str    s = %s\n", s.str);
    printf("在结构体里使用匿名联合\n");
    struct Anonymous_Data adi = {TYPE_INT, {.i=7}},     // C++支持此种初始化方式
                          add = {TYPE_DOUBLE, .d=1.2},
                          ads = {TYPE_STR, .str="May"};
    print_data(&adi);
    print_data(&add);
    print_data(&ads);
    printf("在结构体里使用命名联合\n");
    struct Named_Data ndi = {TYPE_INT, .data={.i=7}},
                      ndd = {TYPE_DOUBLE, {.d=1.2}},
                      nds = {TYPE_STR, {.str="May"}};
    print_data(&ndi);
    print_data(&ndd);
    print_data(&nds);
    return 0;
};