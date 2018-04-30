#include <iostream>
using std::cout; using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

vector<string> process(int num)
{
    if (num == 0)
        return {};
    else
        return {"dad", "defaad", "iuhadga"};
}

string make_plural(size_t ctr, const string &word, 
                               const string &ending)
{
	return (ctr > 1) ? word + ending : word;
}

const string manip(int i)
{   
    string s = "temp";
    if (i == 0)
        return s;                // 不能返回&s 因为s在函数执行完毕后会消失
    else if(i == 1)
        return "ok";
    else
        return 0;
}

const string &ref_manip(int i)   // 这个函数是返回局部对象的引用
{   
    string s = "temp";
    static string call_num = "";
    call_num += "S";

    //return s;                 // 不能返回&s 因为s在函数执行完毕后会消失
    //return "ok";              // 不能返回临时变量
    return call_num;
}

int main()
{   
    int i = 1;
    vector<string> strs;
    strs = process(i);
    cout << strs[0] << ", " << strs[1] << endl;
    i = 0;
    strs = process(i);
    cout << strs.size();

    size_t cnt = 1;
	cout << make_plural(cnt, " success", "es") << endl;

	cnt = 2;
	cout << make_plural(cnt, " failure", "s") << endl;

    string s, ss;
    s = manip(0);
    cout << s << endl;
    s = manip(1);
    cout << s << endl;

    s = ref_manip(2);
    cout << s << endl;
    s += "O";
    cout << s << endl;
    ss = ref_manip(2);
    cout << ss << endl;
    return 0;
}