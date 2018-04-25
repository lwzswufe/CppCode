#ifndef SALES_DATA_H      // #ifndef 判断变量是否未定义
#define SALES_DATA_H      // #define 把名字定义成预处理变量
#include <string>

struct Sales_data {
	std::string bookNo;
#ifdef IN_CLASS_INITS     // #ifdef 判断变量是否已定义
	unsigned units_sold = 0;
	double revenue = 0.0;
#else
	unsigned units_sold;  
	double revenue;
#endif                    // end #ifdef
};
#endif                    // end #ifndef
