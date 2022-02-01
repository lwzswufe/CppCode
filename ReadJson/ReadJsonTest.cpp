#include "ReadJson.h"


// 显示已读取的配置
// void ShowJsonSize(const JsonDictType &config)
// {
//     printf("size:%lu\n", config.size());
// }

int main()
{   
    std::string key1{"dsadq"}, key2{"sdq"}, key3{"list"};
    JsonUnitType unit1{JsonUnitType("sdw")};
    JsonUnitType unit2{JsonUnitType(7)};
    JsonListType list1{unit1, unit2};
    ShowJsonList(list1, 1);
    JsonUnitType unit3{JsonUnitType(list1)};
    printf("create list successful\n");
    JsonDictType json{{key1, unit1}, {key2, unit2}, {key3, unit3}};
    printf("create dict successful\n");
    ShowJson(json);
    return 0;
}