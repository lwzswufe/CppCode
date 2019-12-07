#include <stdio.h>
struct Array
{   
    //implicit conversion 隐式类型转换
    operator int() const { printf("call implicit convet\n"); return arr[0]; }
 
    // explicit conversion 显式类型转换
    explicit operator int*() const { printf("call explicit convet\n"); return nullptr; }
    
    void print() {for (int i = 0; i < 4; i++){printf("%d, ", arr[i]);} printf("\n");};

    int operator+(const int &a) {return arr[0] + a;};

    int operator-(const int &a) {return arr[0] - a;};

    void operator=(const int &a) {arr[0] = a;};

    int arr[4];
};
 
int main()
{
    Array x{1, 2, 3, 4};
    Array y{10, 10, 10, 10};
    printf("struct size: %lu  int size:%lu\n", sizeof(Array), sizeof(int));
    x.print();
    int n = static_cast<int>(x);   // OK: sets n to 7
    printf("n = %d\n", n);
    int m = x;                     // OK: sets m to 7
    printf("m = %d\n", m);
    int* p = static_cast<int*>(x);  // OK: sets p to null
    printf("p = %p\n", p);
    // 实现数组与int之间的运算
    x.print();
    x = 7;
    x.print();
    printf("%d  1 + %d\n", 1 + x, x);
    x.print();
    x = y + 1;
    x.print();
    x = y - 1;
    x.print();
    x = 5 + y;
    x.print();
    x = x + y;
    x.print();
    return 0;
}