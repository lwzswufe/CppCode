//默认参数
#include <iostream>
using std::cout; using std::endl;

#include <string>
using std::string;

void screen(int height=60, int weight=60, string color="red")
{   
    cout << "===============" << endl;
    cout << "height : " << height
         << "\nweight : " << weight
         << "\ncolor  : " << color << endl;
}

int main()
{
    screen();
    screen(3);
    screen(3, 60);
    screen(4, 4, "green");
    //screen(weight=60);   // 错误
}