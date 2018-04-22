#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

int ReadLines()
{
    ifstream ReadFile;
    int n_row = 0;
    string line;
    ReadFile.open( ".\\data\\book_sales", ios::in);

    while(getline(ReadFile, line))
    {
        n_row++;
    }
    return n_row;
}

int main()
{
    int n_row = ReadLines();
    cout << "n_row:" << n_row << endl;
}