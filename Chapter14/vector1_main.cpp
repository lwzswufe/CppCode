#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

#include <cstdio>

#include "vector1.h"

int main()
{   
    Vector v1(5.1, 6);
    v1.show();

    Vector v2(3);
    v2.show();
    
    Vector v3;

    v3 = v1 + v2;
    v3.show();
    //cout << v3 << endl;
    //v2.dim;

    Vector v4 = v3 - v1;
    v4.show();

    cout << v3 << endl;
    if (v4 == v2)
        cout << "v4 == v2" << endl;
    if (v1 != v3)
        cout << "v1 != v3" << endl;

    v4.show();
    v4 += v1;
    v4.show();
    v4 = v4 * 3;
    v4.show();
    v4 = v4 * 0.333;
    v4.show();
    return 0;
}
