#include <iostream>
using std::cout; using std::endl; using std::ostream;

#include <string>
using std::string;

#include <stdio.h>

#include "vector1.h"

int main()
{   
    Vector v1(5.1, 6);
    v1.show();
    cout << v1 << endl;
    Vector v2(3);
    v2.show();
    //v2.dim;

    return 0;
}
