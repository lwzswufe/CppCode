/*
 * 
*/ 

#include <set>
using std::multiset;

#include <map>
using std::map;

#include <string>
using std::string;

#include <utility>
using std::pair; using std::make_pair;

#include <iostream>
using std::cout; using std::endl;

void print(map<auto, auto> dict)
{
	for (auto pair_ : dict)				// dict是由若干个pair构成  pair即key-value
		cout << pair_.first << ": " << pair_.second << endl;
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

int main() 
{
	map <string, size_t> word_count; 		// empty map
	map <string, string> file_path = {
									  {"log", "D:\\log.txt"},	
									  {"err", "C:\\hsda\\da"},	
									  {"trade", ".\\data\\trade.log"}	
									  }; 	// 列表初始化	

	print(file_path);

	word_count["Anna"] = 1;  				// 赋值

	print(word_count);  
	
	++word_count["Anna"];        			// fetch the element and add 1 to it

	print(word_count);

	string word; 							// various ways to add word to word_count 
	word_count.insert({"A", 1});
	word_count.insert(make_pair("B", 1));
	word_count.insert(pair<string, size_t>("C", 1));
	word_count.insert(map<string, size_t>::value_type("D", 1));
	
	print(word_count);
// 	typedef map<string,size_t>::value_type valType;
// 	word_count.insert(valType(word, 1));
	
// 	// use value returned by insert
	pair<map<string, size_t>::iterator, bool> insert_ret;
											// pair类型<迭代器, bool>

	insert_ret = word_count.insert(make_pair("Anna", 1));

	if (insert_ret.second == true)    		// Anna was already in the map
	    insert_ret.first->second++;    		// increment current value
		//等效于++((insert_ret.first)->second)
	print(word_count);

	insert_ret = word_count.insert(make_pair("Bob", 1));
	if (insert_ret.second == false)    		// Bob was not in the map
	    cout << "Bob is not in the map " << endl;
	print(word_count);

	// get an iterator to an element in word_count
	auto map_it = word_count.begin();
	
	// *map_it is a reference to a pair<const string, size_t> object
	cout << map_it->first;         			// prints the key for this element
	cout << " " << map_it->second; 			// prints the value of the element
	++map_it->second;     					// ok: we can change the value through an iterator

	cout << word_count["A"] << endl;
	cout << word_count.at("A") << endl;

	auto cnt = word_count.erase("Bob");
	cout << "delete num:" << cnt << endl;
	cnt = word_count.erase("F");			// F is not in the map
	cout << "delete num:" << cnt << endl;
	print(word_count);

	auto iter =  word_count.find("Anna");	// 若元素在key里 返回指向元素的指针
	cout << iter->first << iter->second << endl;

	auto iter2 =  word_count.find("lsad");	// 若元素不在key里 返回指向元素尾后的指针
	if (iter2 == word_count.end())
		cout << "\"lsad\" is not in the map" << endl;

	word_count.erase(iter);					// 删除迭代器指定的元素
	print(word_count);

	word_count.erase(++word_count.begin(), --word_count.end());
	print(word_count);						// 删除迭代器指定范围的元素

	return 0;
}
