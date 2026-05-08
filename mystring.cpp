#include <iostream>
#include <cstring>
using namespace std;


class MyString
{
    private:
        char *string_ptr;
    public:
        MyString();
        MyString(const char *str_in);
        MyString(const MyString &str);
        ~MyString();

        // operator= reload
        MyString &operator=(const MyString &other);

        void print() const; // print string
        int mystringLen() const; // get the length of the string('\0' not counted in)
};

MyString::MyString()
{
    string_ptr = new char [1];
    string_ptr[0] = '\0';
}

MyString::MyString(const char *str)
{
    int size = strlen(str) + 1;

    string_ptr = new char [size];
    strcpy(string_ptr, str);
    string_ptr[size-1] = '\0';
}

MyString::MyString(const MyString &str)
{
    int size = strlen(str.string_ptr) + 1;

    string_ptr = new char [size];
    strcpy(string_ptr, str.string_ptr);
    string_ptr[size-1] = '\0';
}

MyString::~MyString()
{
    delete [] string_ptr;
    string_ptr = nullptr;
}


MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        int size = strlen(other.string_ptr) + 1;
        delete [] string_ptr;
        string_ptr = new char [size];
        strcpy(string_ptr, other.string_ptr);
        string_ptr[size-1] = '\0';
    }
    return *this;
}


void MyString::print() const 
{
    int i=0;
    while (string_ptr[i] != '\0')
    {
        cout << string_ptr[i];
        i ++;
    }
    cout << endl;
}

int MyString::mystringLen() const 
{
    return strlen(string_ptr);
}

int main()
{
    MyString my_str((char*)"Hello");

    // test print()
    my_str.print();
    // test mystringLen()
    cout << "length: " << my_str.mystringLen() << endl;

    return 0;
}
