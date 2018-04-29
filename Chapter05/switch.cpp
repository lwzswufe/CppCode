//swith
#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <string>
using std::string;

int main()
{
    // initialize counters for each vowel
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0;
    string s = "if ch is a vowel, increment the appropriate counter";

    for (char ch : s) 
	{
    	switch (ch) 
		{	
    		case 'a':                  // 匹配到 'a'
    			++aCnt;
    			break;
    		case 'e':
    			++eCnt;
    			break;
    		case 'i':
    			++iCnt;
    			break;
    		case 'o':
    			++oCnt;
    			break;
    		case 'u':
    			++uCnt;
    			break;
			default:                   // 未匹配到的情况
				++otherCnt;
				break;
    	}
    }

    cout << "Number of vowel a: \t" << aCnt << '\n'
         << "Number of vowel e: \t" << eCnt << '\n'
         << "Number of vowel i: \t" << iCnt << '\n'
         << "Number of vowel o: \t" << oCnt << '\n'
         << "Number of vowel u: \t" << uCnt << '\n'
		 << "Number of nonvowel:\t" << otherCnt << endl;

	cout << "没有用break跳出 case的情况会重复计数，" << 
	        "若第i种情况匹配， 第i+1及以后的分类都会计数+1：" << endl;
	aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, otherCnt = 0;

	for (char ch : s) 
	{
    	switch (ch) 
		{
    		case 'a':                  // 匹配到 'a'
    			++aCnt;                
    		case 'e':
    			++eCnt;                // = a+e
    		case 'i':
    			++iCnt;                // = a+e+i
    		case 'o':
    			++oCnt;                // = a+e+i+o
    		case 'u':
    			++uCnt;                // = a+e+i+o+u
			default:                   // 未匹配到的情况
				++otherCnt;            // = all
    	}
    }

    cout << "Number of vowel a: \t" << aCnt << '\n'
         << "Number of vowel e: \t" << eCnt << '\n'
         << "Number of vowel i: \t" << iCnt << '\n'
         << "Number of vowel o: \t" << oCnt << '\n'
         << "Number of vowel u: \t" << uCnt << '\n'
		 << "Number of nonvowel:\t" << otherCnt << endl;

	cout << "另一种模式:" << endl;

	int vowelCnt = 0;
	otherCnt = 0;

	for (char ch : s) 
	{
    	switch (ch) 
		{
    		case 'a':                  // 匹配到 'a'
    		case 'e':
    		case 'i':
    		case 'o':
    		case 'u':
    			++vowelCnt;
				break;
			case ' ':
				continue;
			default:                   // 未匹配到的情况
				++otherCnt;
				break;
    	}
    }

    cout << "Number of vowel:   \t" << vowelCnt << '\n'
		 << "Number of nonvowel:\t" << otherCnt << endl;

    return 0;
}
