

#include <iostream>
using std::cout; using std::endl;

// namespace A and function f are defined at global scope
namespace A 
{
    int i = 0, j = 42;
}

void f() 
{
    using namespace A; // injects the names from A into the global scope

	// uses i and j from namespace A
    cout << "i: " << i << " j: " << j << endl;
}

namespace blip 
{
    int i = 16, j = 15, k = 23;
	void f() 
		{ cout << "i: " << i << " j: " << j << " k: " << k << endl; }
}

int j = 0;                  // ok: j inside blip is hidden inside a namespace

int main() 
{
                            // using directive; 
	                        // the names in blip are ``added'' to the global scope
    using namespace blip;   // clash between ::j and blip::j
                            // detected only if j is used

    //++j;                  // 这个j有二义性 会报错 error: reference to 'j' is ambiguous
    ++i;                    // sets blip::i to 17
    ++::j;                  // ok: sets global j to 1
    ++blip::j;              // ok: sets blip::j to 16

    int k = 97;             // local k hides blip::k
    ++k;                    // sets local k to 98

	::f();                  // 使用全局变量中的f()  
	blip::f();              // 使用blip中的f
	cout << "j: " << ::j << " k: " << k << endl; 

	return 0;
}
