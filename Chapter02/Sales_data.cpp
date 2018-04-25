#include <iostream>
#include <string>
#include "Sales_data.h"

int main()
{
	Sales_data data1;

	double price = 10.00;  
	int units_sold = 3;
	std::string bookNo = "0-201-70353-X";

	data1.bookNo = bookNo;  
	data1.units_sold = units_sold;

	data1.revenue = data1.units_sold * price;
	std::cout << "data1 sales: " << data1.revenue << std::endl;
}
