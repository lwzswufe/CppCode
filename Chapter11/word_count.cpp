/*
*/ 

#include <map>
using std::map;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <fstream>
using std::ifstream; 

int main() 
{
    // count the number of times each word occurs in the input
    string word;
	ifstream input;                         	// 定义读取类
    input.open("read.txt");                    	// 打开文件
    map<string, size_t> word_count; 
    while (input >> word)
		++word_count[word];

	for (const auto &w : word_count)
		cout <<  w.first << " occurs " << w.second << " times" << endl;

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    
    auto map_it = word_count.cbegin();
    while (map_it != word_count.cend()) {

        cout << map_it->first << " occurs " 
             << map_it->second << " times" << endl;
        ++map_it;  
    }

	return 0;
}

