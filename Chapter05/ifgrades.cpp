#include <iostream>
using std::endl; using std::cin; using std::cout;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iterator>
using std::begin; using std::end;

#ifdef LIST_INIT
const vector<string> scores = {"F", "D", "C", "B", "A", "A++"};
#else
// in this program just use an array instead of a vector,
// we only use scores to fetch values so don't need the flexibility of a vector
const string scores[] = {"F", "D", "C", "B", "A", "A++"};
#endif

// these functions demonstrate alternative ways to handle the if tests
// function that takes an unsigned value and a string 
// and returns a string
string goodVers(string lettergrade, unsigned grade)
{
	if (grade % 10 > 7)
		lettergrade += '+';	      // grades ending in 8 or 9 get a '+'
	else 
		if (grade % 10 < 3)
			lettergrade += '-';   // those ending in 0, 1, or 2 get a '-'
	return lettergrade;
}

// incorrect version of the function to add a plus or minus to a grade
string badVers(string lettergrade, unsigned grade)
{
	if (grade % 10 >= 3) 
		if (grade % 10 > 7) 
			lettergrade += '+';   // grades ending in 8 or 9 get a +
	else
		lettergrade += '-';       // grades ending in 3, 4, 5, 6 will get a minus!
	return lettergrade;
}

// corrected version using the same logic path as badVers
string rightVers(string lettergrade, unsigned grade)
{
	if (grade % 10 >= 3) 
	{
		if (grade % 10 > 7) 
			lettergrade += '+';   // grades ending in 8 or 9 get a +
	} 
	else                          // curlies force the else to go with the outer if
		lettergrade += '-';       // grades ending in 0, 1, or 2 will get a minus
	return lettergrade;
}

int main()
{
	unsigned grade;
	unsigned grades[] = {67, 78, 96, 56, 100, 37, 28, 83};

	// now process those grades
	for (auto it : grades)                            // for each grade we read
	{
		cout << it << " " ;                           // print the grade
		string lettergrade;                           // hold coresponding letter grade
		                                              // if failing grade, no need to check for a plus or minus
		if (it < 60)
			lettergrade = scores[0];
		else 
		{                                             // {"F", "D", "C", "B", "A", "A++"}
			lettergrade = scores[(it - 50)/10];       // fetch the letter grade
			if (it != 100)                            // add plus or minus only if not already an A++
				if (it % 10 > 7)
					lettergrade += '+';               // grades ending in 8 or 9 get a +
				else if (it % 10 < 3)
					lettergrade += '-';               // grades ending in 0, 1, or 2 get a -
		}
		cout << lettergrade << endl;
		if (it > 59 && it !=100) {
			cout << "alternative versions: " << it << " ";
			                                          // start over with just the basic grade, no + or -
			lettergrade = scores[(it - 50)/10];
			cout << goodVers(lettergrade, it) << " ";
			cout << badVers(lettergrade, it) << " ";
			cout << rightVers(lettergrade, it) << " ";
			cout << endl;
		}
	}

	return 0;
}
