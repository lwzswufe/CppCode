

#include <iostream>
using std::cout; using std::endl;

#include <exception>
using std::exception; using std::runtime_error; using std::logic_error;

// this function will compile, even though it clearly violates its exception specification
void f() noexcept                   // promises not to throw any exception
{
    throw exception();              // violates the exception specification
}                                   // 若一个声明了 noexcept的函数抛出异常 则程序会立即终止

void g() { }                               
void h() noexcept(noexcept(f()))    // noexcept(e) 根据e的类型来判定 此函数是不是 noexcept
{ 
    f();                            // 这里说明 若f是noexcept 则 h是noexcept
} 
void i() noexcept(noexcept(g())) { g(); }

int main()
{
    try 
    {
		cout << "f: " << std::boolalpha << noexcept(f()) << endl;
		cout << "g: " << std::boolalpha << noexcept(g()) << endl;
		cout << "h: " << std::boolalpha << noexcept(h()) << endl;
		cout << "i: " << std::boolalpha << noexcept(i()) << endl;
        f();
    } 
    catch (exception &e) 
    {   
        // cout << "caught " << endl;
        cout << "caught " << e.what() << endl;
    }
	
	return 0;
}



