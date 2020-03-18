#include <stdio.h>
#include <math.h>

int main()
{   
    double d = nan("Not A Number");
    printf("d = %lf  d * 1 = %lf d * 0 = %lf d + 1 = %lf\n", d, d * 1, d * 0, d + 1);
    return 0;
}