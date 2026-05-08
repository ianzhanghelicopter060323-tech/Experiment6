#include <iostream>
#include <cstring>
using namespace std;


int main()
{
    char *str = new char [50];
    str[0] = '1';
    cout << "length: " << strlen(str) << endl;

    return 0; 
}