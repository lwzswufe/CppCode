#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int ival = 1024;
    int *pi = &ival;   // pi 指向一个int对象   pi points to an int
    int **ppi = &pi;   // ppi指向一个指针      ppi points to a pointer to an int
    cout << "The value of ival\n"
         << "direct value: " << ival << "\n"
         << "object address: " << pi << "\n"
         << "indirect value: " << *pi << "\n"
         << "pointer address: " << ppi << "\n"
         << "doubly indirect value: " << **ppi
         << endl;

	int i = 2; 
	int *p1 = &i;     // p1 指向 i       p1 points to i
	*p1 = *p1 * *p1;  // equivalent to i = i * i
	cout << "i  = " << i << endl;

	*p1 *= *p1;       // equivalent to i *= i
	cout << "i  = " << i << endl;

    int *p0 = nullptr;
    cout << "empty pointer address" << p0 << endl;

	return 0;
}
