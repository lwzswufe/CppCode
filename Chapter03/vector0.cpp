#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cin; using std::cout; using std::endl;

int main()
{
	// hold the grades we read from the standard input
	vector<unsigned> grades;
    vector<unsigned> score_0(grades);          // 仅仅是赋予初值 
    vector<unsigned> score_1 = grades;
    vector<int> score_2(10, 0);
    vector<int> score_3(10);                   // 未赋值时值为0 
    vector<int> score_4{2, 3, 5, 7};
    vector<unsigned> score_5 = {2, 3, 5, 7};

    grades = score_5;
    cout << "grades: ";
    for (auto i: grades)
        cout << i << ',';
    cout << ' ' <<endl;

    cout << "score_0: " << endl;
    for (auto i: score_0)
        std::cout << i << ' ';
    cout << endl;

    cout << "score_1: " << endl;
    for (auto i: score_1)
        std::cout << i << ' ';
    cout << endl;

    cout << "score_3: " << endl;
    for (auto i: score_3)
        std::cout << i << ' ';
    cout << endl;
    score_3[0] = 1;
    cout << "score_3: " << endl;
    for (auto i: score_3)
        std::cout << i << ' ';
    cout << endl;

    for (auto i: score_4)
        score_0.push_back(i);

    cout << "score_0: " << endl;
    for (auto i: score_0)
        std::cout << i << ' ';
    cout << endl;
    return 0;
}
