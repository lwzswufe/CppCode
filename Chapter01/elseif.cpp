#include <iostream>

using namespace std;

int choose(int x)
{   
    int r;
    if (x < 7)
        return 0;
    else if (x < 11)
    {   
        r = 1;
        return 1;
    }
    else if (x < 13)
        return 2;
    else
    {   
        r = 2;
        return 3;
    }
    return -1;
}

int main()
{
    for(int i=5; i<15; i++)
        cout << i << "->" << choose(i) << endl;
    return 0;
}