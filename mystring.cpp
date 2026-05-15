#include <iostream>
using namespace std;


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
        MyString operator+(const MyString &othter);
        
        MyString &operator++();     // ++ string
        MyString &operator++(int);  // string ++

        friend ostream &operator<<(ostream &out, const MyString &str);

        // string operator function
        // insert <char>str_to_insert in pos <int>i
        void insert(char str_to_insert, int i);
        // insert <char *>str_to_insert in pos <int>i
        void insert(const char *str_to_insert, int i);
        // insert <MyString>str_to_insert in pos <int>i
        void insert(const MyString &str_to_insert, int i);

        // string capitalization
        void capitalize();
        // move number elements in order at rear 
        void moveNumber();
        // string pairing
        // SUCCEED: 1 FAILED: -1
        static int strPair(MyString my_str_local, MyString ny_str_to_pair);

        void print() const; // print string
        int mystringLen() const; // get the length of the string('\0' not counted in)
};


/*============ self-defined string operator functions defination ============*/
int stringLen(const char *str);
void stringCopy(char *str_dest, const char *str_src);
/*===========================================================================*/


/*================ construct & deconstruct functions ======================*/
MyString::MyString()
{
    string_ptr = new char [1];
    string_ptr[0] = '\0';
}

MyString::MyString(const char *str)
{
    int size = stringLen(str) + 1;

    string_ptr = new char [size];
    stringCopy(string_ptr, str);
    string_ptr[size-1] = '\0';
}

MyString::MyString(const MyString &str)
{
    int size = stringLen(str.string_ptr) + 1;

    string_ptr = new char [size];
    stringCopy(string_ptr, str.string_ptr);
    string_ptr[size-1] = '\0';
}

MyString::MyString(const string &str)
{
    int size = stringLen(str.c_str()) + 1;

    string_ptr = new char [size];
    stringCopy(string_ptr, str.c_str());
    string_ptr[size-1] = '\0';
}

MyString::~MyString()
{
    delete [] string_ptr;
    string_ptr = nullptr;
}
/*========================================================================*/


/*===================== operator reload ==================================*/
MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        int size = stringLen(other.string_ptr) + 1;
        delete [] string_ptr;
        string_ptr = new char [size];
        stringCopy(string_ptr, other.string_ptr);
        string_ptr[size-1] = '\0';
    }
    return *this;
}

MyString MyString::operator+(const MyString &other)
{
    int size_local = this->mystringLen();

    // construct new MyString
    MyString string_temp(*this);
    // insert other at rear
    string_temp.insert(other, size_local);
    
    return string_temp;
}

// ++ string
// move first element to the rear
MyString &MyString::operator++()
{   
    char head = this->string_ptr[0];
    int size = this->mystringLen();

    // empty-length check
    if (size <= 1)
    {
        return *this;
    }

    // move forward
    for (int i=0; i<size; i++)
    {
        this->string_ptr[i] = this->string_ptr[i+1];
    }
    this->string_ptr[size-1] = head;

    return *this;
}

// string ++
// move last element to the head
MyString &MyString::operator++(int) 
{
    int size = this->mystringLen();
    char rear = this->string_ptr[size-1];

    // empty-length check
    if (size <= 1)
    {
        return *this;
    }

    // move backward
   for (int i=size-1; i>=1; i--)
    {
        this->string_ptr[i] = this->string_ptr[i-1];
    }
    this->string_ptr[0] = rear;

    return *this;
}

// operator<< reload
ostream &operator<<(ostream &out, const MyString &str)
{
    for (int i=0; str.string_ptr[i] != '\0'; i++)
    {
        out << str.string_ptr[i];
    }

    return out;
}

/*========================================================================*/


/*==================== tring opearting functions =========================*/
// insert <char>str_to_insert in pos <int>i
void MyString::insert(char str_to_insert, int i) 
{
    char temp[2] = {str_to_insert, '\0'};
    insert(temp, i);
}

// insert <char *>str_to_insert in pos <int>i
void MyString::insert(const char *str_to_insert, int i)
{
    int old_size = stringLen(string_ptr);
    int insert_size = stringLen(str_to_insert);

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

// insert <MyString>str_to_insert in pos <int>i
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

void MyString::moveNumber()
{
    int len = stringLen(string_ptr); // create new array instead of moving elements in original array
    char *new_string_ptr = new char [len + 1];
    int index = 0;

    for (int i = 0; i < len; i ++)
    {
        if (!(string_ptr[i] >= '0' && string_ptr[i] <= '9'))
        {
            new_string_ptr[index] = string_ptr[i];
            index ++;
        }
    }

    for (int i = 0; i < len; i ++)
    {
        if (string_ptr[i] >= '0' && string_ptr[i] <= '9')
        {
            new_string_ptr[index] = string_ptr[i];
            index ++;
        }
    }

    new_string_ptr[index] = '\0';
    delete [] string_ptr;
    string_ptr = new_string_ptr;
}

int MyString::strPair(MyString my_str_local, MyString my_str_to_pair)
{
    int size_local = stringLen(my_str_local.string_ptr);
    int size_pair = stringLen(my_str_to_pair.string_ptr);

    if (size_local != size_pair) // if len not equal, straight FAIL
        return -1;
    
    // otherwise size_local == size_pair
    // int size = size_local;
    int i = 0;
    while (my_str_local.string_ptr[i] != '\0')
    {
        if (my_str_local.string_ptr[i] != my_str_to_pair.string_ptr[i]) // exist unpairing element
        {
            return -1;
        }

        i ++;
    }

    return 1;
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
    return stringLen(string_ptr);
}
/*========================================================================*/


/*===================== global string functions ===========================*/
int stringLen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len ++;
    }

    return len;
}

void stringCopy(char *str_dest, const char *str_src)
{
    int i = 0;
    while (str_src[i] != '\0')
    {
        str_dest[i] = str_src[i];
        i ++;
    }
    str_dest[i] = '\0';
}
/*========================================================================*/


int main()
{
    // operator= reload test
    MyString my_str_equal;
    MyString my_str_string((char *)"world");
    my_str_equal = my_str_string;
    cout << "operator= reload: " << my_str_equal << endl;

    // operator+ reload test
    MyString my_str_char((char *)"hello");
    MyString my_str_add_other((char *)"world");
    MyString my_str_add = my_str_char + my_str_add_other;
    cout << "operator+ reload: " << my_str_add << endl;

    // operator++ reload test
    MyString my_str_left((char *)"abcd");
    ++ my_str_left;
    cout << "operator++ reload: " << my_str_left << endl;

    // operator++(int) reload test
    MyString my_str_right((char *)"abcd");
    my_str_right ++;
    cout << "operator++(int) reload: " << my_str_right << endl;

    // operator<< reload test
    MyString my_str_output((char *)"hello");
    cout << "operator<< reload: " << my_str_output << endl;

    // insert <char>str test
    MyString my_str_insert_char((char *)"helo");
    my_str_insert_char.insert('l', 3);
    cout << "insert <char>str: " << my_str_insert_char << endl;

    // insert <char *>str test
    MyString my_str_insert_char_ptr((char *)"he");
    my_str_insert_char_ptr.insert((char *)"llo", 2);
    cout << "insert <char *>str: " << my_str_insert_char_ptr << endl;

    // insert <MyString>str test
    MyString my_str_insert_base((char *)"he");
    MyString my_str_insert_other((char *)"llo");
    my_str_insert_base.insert(my_str_insert_other, 2);
    cout << "insert <MyString>str: " << my_str_insert_base << endl;

    // capitalization function test
    MyString my_str_capital((char *)"HeLlo");
    my_str_capital.capitalize();
    cout << "capitalization function: " << my_str_capital << endl;

    // move number function test
    MyString my_str_number((char *)"H1e2l3lo");
    my_str_number.moveNumber();
    cout << "move number function: " << my_str_number << endl;

    // string pairing function test
    MyString my_str_pair_1((char *)"hello");
    MyString my_str_pair_2((char *)"hello");
    MyString my_str_pair_3((char *)"world");
    cout << "pairing succeed code: " << MyString::strPair(my_str_pair_1, my_str_pair_2) << endl;
    cout << "pairing failed code: " << MyString::strPair(my_str_pair_1, my_str_pair_3) << endl;

    // print function test
    MyString my_str_print((char *)"hello");
    cout << "print function: ";
    my_str_print.print();

    // mystringLen function test
    MyString my_str_len((char *)"hello");
    cout << "mystringLen function: " << my_str_len.mystringLen() << endl;

    return 0;
}
