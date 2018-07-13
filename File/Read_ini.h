#include <map>
#include <fstream>
#include <cstring>


void line_parse(char line[256], std::string &key, std::string &value)
{   // 拆分一行字符串  
    char * pch_1;
    char * pch_2;
    char * next_token = NULL;
    pch_1   = strtok_s(line, "= []\n", &next_token);
    if (pch_1 != NULL)
        key = pch_1;
    else
        key = "";

    pch_2 = strtok_s(NULL, "= []\n", &next_token);
    if (pch_2 != NULL)
        value = pch_2;
    else
        value = "";
}


std::map<std::string, std::map<std::string, std::string>> 
Read_ini(char filename[100])
{   // 读取配置文件
    size_t line_size{256};
    char line[line_size];
    std::string key, value, temp_key{""};

    std::map<std::string, std::map<std::string, std::string>> config;
    std::ifstream input;

    input.open(filename);

    while(!input.eof())
    {
        input.getline(line, line_size);
        line_parse(line, key, value);
        if (key == "")
        {
            continue;
        }
        if (value == "")
        {   
            std::map<std::string, std::string> temp_map;
            config[key] = temp_map;
            temp_key = key;
        }
        else
        {
            config[temp_key][key] = value;
        }
    }
    return config;
}

void show_ini(std::map<std::string, std::map<std::string, std::string>> config)
{   //显示配置文件的内容
    char buffer[100];
    for (auto i= config.begin(); i!= config.end(); i++)
    {   
        std::string key = i->first;
        auto value      = i->second;
        sprintf_s(buffer, "[%s]:\n", key.data());
        fputs (buffer , stdout);  
        for (auto ii= value.begin(); ii != value.end(); ii++)
        {
            std::string key_   = ii->first;
            std::string value_ = ii->second;
            sprintf_s(buffer, "        <%s : %s>\n", key_.data(), value_.data());
            fputs (buffer , stdout);  
        }
    }
}