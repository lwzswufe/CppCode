#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

class BarsData
{   
public:
    BarsData() {count++;};
    // 声明类变量
    static int count;
    // 声明类变量
    static vector<int> vi;
    // 类函数
    static void show() {cout << "count:" << count << " vector:{"; for (int i: vi) cout << i << ", "; cout << "}" << endl;};
    // 实例函数
    void add(int i) {vi.push_back(i);};
};

// 定义和初始化类变量
int BarsData::count = 0;
// 定义和初始化类变量
vector<int> BarsData::vi = {};