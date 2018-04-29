#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::cerr;

/* 
err对应标准错误流，用于显示错误消息。默认情况下被关联到标准输出流，
但它不被缓冲，也就说错误消息可以直接发送到显示器，而无需等到缓冲区
或者新的换行符时，才被显示。一般情况下不被重定向。
*/

int main() 
{
	unsigned grades[] = {67, 78, 96, 56, 100, 37, 28, 83};
	int idx[] = {0, 7, -1, 99};
	int size = 8;

	for (int x : idx)
	{
	    try 
		{
	        if (x >= 8 || x < 0)
			{
				cerr << "error index: " << x << endl;   // 仅输出错误信息
	            throw runtime_error("idx error");       // 抛出异常
			}

	        cout << "idx reght, value= " << grades[x] << endl;
	    } 
		catch (runtime_error err)                       // 捕获异常
		{
	        cout << "error msg: " << err.what() << endl; 
	    }                                                // ends the catch clause
	}                                                    // ends the while loop
	
	return 0;                                            // indicate success
}
