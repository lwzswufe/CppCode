/*
宏的使用
用宏定义函数
*/
#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

#define print(x) cout << x << endl;         // 通过宏定义函数 
#define print_name(x) cout << #x << endl;   // 通过宏定义函数 参数前加#表示参数x的名称
#define hello() cout << "hello" << endl;

int main()
{
    for (int i=0;i<3;i++)
    {
        print(i);
        #ifdef hello                        // 宏在for循环体内部
            print("define hello");  
        #else                               //
            print("no difine hello");
        #endif                              // 必须要endif
    }
    hello();
    string str{"param_name"};

    print(str);
    print_name(str);

    #ifndef hello2
        print("no define hello2")
    #endif

    #undef hello                        // 将宏设置为未定义 在这句话以后我们将不能使用该宏

    #ifdef hello                        // hello在for循环体内部
        print("define hello");  
    #else                               //
        print("no difine hello");
    #endif                       

    
    cout <<   "filename: " << __FILE__
         << "\nline_num: " << __LINE__
         << "\nCompiled: " << __DATE__
         << "\ntime    : " << __TIME__
         << "\nfun_name: " << __func__
         << endl;

    return 0;
}