#include <iostream>
#include <cstring>
using namespace std;

int charLen(const char *str)
{
    int len = 0;
    while (str != nullptr && str[len] != '\0')
    {
        len ++;
    }
    return len;
}


class MyString
{
    private:
        char *string_ptr;
    public:
        MyString();
        MyString(const char *str_in);
        MyString(const MyString &str); // copy construct function with parameter MyString &str
        MyString(const string &str);   // copy construct function with parameter string &str
        ~MyString();

        // operator= reload
        MyString &operator=(const MyString &other);

        // insetation function
        // insert <char>str_to_insert in pos <int>i
        void insert(char str_to_insert, int i);
        // insert <char *>str_to_insert in pos <int>i
        void insert(const char *str_to_insert, int i);
        // insert <MyString>str_to_insert in pos <int>i
        void insert(const MyString &str_to_insert, int i);

        // string capitalization
        void capitalize();

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

MyString::MyString(const string &str)
{
    int size = strlen(str.c_str()) + 1;

    string_ptr = new char [size];
    strcpy(string_ptr, str.c_str());
    string_ptr[size-1] = '\0';
}

MyString::~MyString()
{
    delete [] string_ptr;
    string_ptr = nullptr;
}


void MyString::insert(char str_to_insert, int i) 
{
    char temp[2] = {str_to_insert, '\0'};
    insert(temp, i);
}

void MyString::insert(const char *str_to_insert, int i)
{
    int old_size = strlen(string_ptr);
    int insert_size = strlen(str_to_insert);

    if (i < 0 || i > old_size)
    {
        cout << "ERROR! invalid insert position" << endl;
        return ;
    }


    char *new_string_ptr = new char [old_size + insert_size + 1];
    int index = 0;

    for (int j = 0; j < i; j ++)
    {
        new_string_ptr[index] = string_ptr[j]; // source string copy
        index ++;
    }

    for (int j = 0; j < insert_size; j ++)
    {
        new_string_ptr[index] = str_to_insert[j]; // copy str_to_insert at specific place
        index ++;
    }

    for (int j = i; j < old_size; j ++)
    {
        new_string_ptr[index] = string_ptr[j]; // move string after postion i backward
        index ++;
    }

    new_string_ptr[index] = '\0';
    delete [] string_ptr;
    string_ptr = new_string_ptr;
}

void MyString::insert(const MyString &str_to_insert, int i)
{
    insert(str_to_insert.string_ptr, i);
}


void MyString::capitalize()
{
    int i=0;
    while (string_ptr[i] != '\0')
    {
        if (string_ptr[i] >= 'a' && string_ptr[i] <= 'z')
        {
            string_ptr[i] += ('A' - 'a');
        }
        
        i ++;
    }
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
    MyString my_str((char*)"H1e1l4l5o||");

    // test string-to-MyString
    string str = "Sieg Heil";
    MyString my_str_1(str);

    // insert <char *>str
    my_str_1.insert(my_str, 2);

    // capitalization function test
    my_str.capitalize();

    // test envalue operator
    MyString my_str_2 = my_str_1;

    // test print()
    my_str.print();
    my_str_1.print();
    my_str_2.print();

    // test mystringLen()
    cout << "length: " << my_str.mystringLen() << endl;
    cout << "length1: " << my_str_1.mystringLen() << endl;
    cout << "length2: " << my_str_2.mystringLen() << endl;

    return 0;
}
