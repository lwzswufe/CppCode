/*
 * 
*/ 

#include <set>
using std::multiset;

#include <map>
using std::map; using std::multimap;

#include <string>
using std::string;

#include <utility>
using std::pair; using std::make_pair;

#include <iostream>
using std::cout; using std::endl;

void print(multimap<auto, auto> dict)
{
	for (auto pair_ : dict)				// dict是由若干个pair构成  pair即key-value
		cout << pair_.first << ": " << pair_.second << endl;
	cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
}

int main() 
{
	multimap <string, size_t> word_count; 		// empty map
	multimap <string, string> file_path = {
									  {"log", "D:\\log.txt"},	
                    {"log", "D:\\buy.log"},	
									  {"err", "C:\\hsda\\da"},
                    {"log", "D:\\sell.log"},	
                    {"err", "C:\\hsda\\da.txt"},	
									  {"trade", ".\\data\\trade.log"}	
									  }; 	// 列表初始化	

	print(file_path);

  // word_count["Anna"] = 1;  				// 不支持multimap
  word_count.insert({"A", 1});

	print(word_count);  
	
	word_count.insert({"A", 3});        // 重复插入

	print(word_count);

	string word; 							// various ways to add word to word_count 
	word_count.insert({"A", 4});
	word_count.insert(make_pair("B", 1));
  word_count.insert(make_pair("B", 3));
	word_count.insert(pair<string, size_t>("C", 1));
	word_count.insert(map<string, size_t>::value_type("D", 1));
	
	print(word_count);

	multimap<string, size_t>::iterator insert_ret;
											// multimap的insert返回迭代器

	insert_ret = word_count.insert(make_pair("A", 7)); 
                      // 返回插入pair的迭代器

  cout << insert_ret->first << ": "
       << insert_ret->second << endl;
  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

	// get an iterator to an element in word_count
	auto map_it = word_count.begin();
	
	// *map_it is a reference to a pair<const string, size_t> object
	cout << map_it->first;         		   	// prints the key for this element
	cout << ": " << map_it->second; 			// prints the value of the element
  cout << endl;
	++map_it->second;     					      // ok: we can change the value through an iterator

	auto cnt = word_count.erase("B");
	cout << "delete num:" << cnt << endl;
	cnt = word_count.erase("F");			    // F is not in the map
	cout << "delete num:" << cnt << endl;
	print(word_count);

	auto iter =  word_count.find("A");	  // 若元素在key里 返回指向元素的指针
	cout << iter->first << iter->second << endl;

  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

  for(auto beg = word_count.lower_bound("A"), //指向匹配的第一个元素的位置
           end = word_count.upper_bound("A"); //指向匹配的最后一个元素的位置
      beg != end; ++beg)
      cout << beg->first << ": "
           << beg->second <<endl;
  
  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

  for(auto pos = word_count.equal_range("A"); // pair<匹配的第一个元素的位置, 匹配的最后一个元素的位置>
      pos.first != pos.second; 
      ++pos.first)
      cout << pos.first->first << ": "
           << pos.first->second <<endl;

  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

  print(word_count);
  iter =  word_count.find("A");	  // 若元素在key里 返回指向第一个元素的指针
	word_count.erase(iter);					// 删除迭代器指定的元素
	print(word_count);

	word_count.erase(word_count.lower_bound("A"), word_count.upper_bound("A"));
	print(word_count);						  // 删除迭代器指定范围的元素

	return 0;
}

