#include <iostream>
using std::endl; using std::flush; using std::ends;
using std::unitbuf; using std::nounitbuf; using std::cout;

int main()
{
							// writes hi and a newline, then flushes the buffer
    cout << "hi!" << endl;  // print with /n
							// writes hi, then flushes the buffer; adds no data
    cout << "hi!" << flush; // print with null
							// writes hi and a null, then flushes the buffer
    cout << "hi!" << ends;  // print with /0

    cout << unitbuf;        // all writes will be flushed immediately
							// any output is flushed immediately, no buffering
    cout << "first" << " second";

	cout << nounitbuf;       // returns to normal buffering

	return 0;
}
