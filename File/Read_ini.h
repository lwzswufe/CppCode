#include <map>
#include <fstream>
#include <cstring>
#include <iostream>
using std::cerr; using std::cout; using std::endl; using std::ends;

std::map<std::string, std::map<std::string, std::string>> 
Read_ini(char filename[100])
{   
    char line[256];
    std::string key, value, temp_key{""};
    std::map<std::string, std::string> temp_map;
    std::map<std::string, std::map<std::string, std::string>> config;
    std::ifstream input;
    input.open(filename);
    while(!input.eof())
    {
        getline(input, line);
        line_parse(line, key, value);
        if (key == "")
        {
            continue;
        }
        if (value == "")
        {   
            if (temp_key == "")
            {   
                config[temp_key] = temp_map;
                temp_map.clear();
            }
            temp_key = key;
        }
        else
        {
            temp_map[key] = value;
        }
    }
    if (temp_key == "")
    {   
        config[temp_key] = temp_map;
        temp_map.clear();
    }
    return config;
}

void line_parse(char line[256], std::string &key, std::string &value)
{
    char * pch_1;
    char * pch_2;
    pch_1   = strtok(line, "= []\n");
    if (pch_1 != NULL)
        key = pch_1;
    else
        key = "";

    pch_2 = strtok(NULL, "= []\n");
    if (pch_2 != NULL)
        value = pch_2;
    else
        value = "";

    //cout << key << ": " << value << endl;
}
