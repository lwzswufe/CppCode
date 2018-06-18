/*
*/ 

#include <iterator>
using std::begin; using std::end;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <tuple>
using std::tuple; using std::get; 
using std::tuple_size; using std::tuple_element;
using std::make_tuple;

#include <string>
using std::string; 

#include <iostream>
using std::cout; using std::endl; 

int main()
{
	tuple<const char*, int, double> item = make_tuple("0-999-78345-X", 3, 20.00);
	const char* book = get<0>(item);      		// returns the 1st member of item
	int cnt = get<1>(item);       		  		// returns the 2nd member of item
	double price = get<2>(item)/cnt; 			// returns the 3rd member of item
	get<2>(item) *= 0.8;           				// apply 20% discount
	
	cout << book << " " << cnt << " " << price << endl;

	typedef decltype(item) trans; 				// trans is the type of item 
												// returns the number of members in object's of type trans
	size_t sz = tuple_size<trans>::value;  		// returns 3 返回tuple的大小
												// cnt has the same type as the second member in item
	tuple_element<1, trans>::type cnt2 = get<1>(item);  // int cnt2 
	tuple_element<0, trans>::type book2 = get<0>(item); // const char* book2
	tuple_element<2, trans>::type price2 = get<2>(item);// double price2
	cout << "size: " << tuple_size<trans>::value << endl;
	
	cout << book2 << " " << cnt2 << " " << price2 << endl;
	
	tuple<size_t, size_t, size_t> threeD;  		// all three members set to 0

	tuple<size_t, size_t, size_t> threeD2(1, 2, 3);

	cout << get<0>(threeD2) << get<1>(threeD2) << get<2>(threeD2) << endl;
	
	return 0;
}
