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

/*================ construct & deconstruct functions ======================*/
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
/*========================================================================*/


/*===================== operator reload ==================================*/
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

MyString MyString::operator+(const MyString &other)
{
    int size_other = other.mystringLen();
    int size_local = this->mystringLen();
    int size_result = size_other + size_local;

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
    int len = strlen(string_ptr); // create new array instead of moving elements in original array
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
    int size_local = strlen(my_str_local.string_ptr);
    int size_pair = strlen(my_str_to_pair.string_ptr);

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
    return strlen(string_ptr);
}
/*========================================================================*/


int main()
{
    MyString my_str((char*)"H1e2llo");

    // test string-to-MyString
    string str = "Sieg Heil";
    MyString my_str_1(str);

    // insert <char *>str
    my_str_1.insert(my_str, 2);

    // capitalization function test
    my_str.capitalize();
    // move number function test
    my_str.moveNumber();

    // test envalue operator
    MyString my_str_2 = my_str_1;

    // pairng check
    cout << "pairing code: " << MyString::strPair(my_str_2, my_str) << endl;

    // test print()
    my_str.print();
    my_str_1.print();
    my_str_2.print();

    // opeartor reload test
    MyString mystr_cpy1 = my_str;
    MyString mystr_add1 = my_str_1 + my_str_2;

    cout << "test opeartor reload: " << endl;
    mystr_cpy1.print();
    mystr_add1.print();

    MyString mystr_plustest((char *)"abcd");

    cout << "operator++ reload: " << endl;
    mystr_plustest.print();
    (++ mystr_plustest).print();
    (mystr_plustest ++).print();

    cout << "operator<< reload: " << endl;
    cout << my_str << endl;

    // test mystringLen()
    cout << "length: " << my_str.mystringLen() << endl;
    cout << "length1: " << my_str_1.mystringLen() << endl;
    cout << "length2: " << my_str_2.mystringLen() << endl;

    return 0;
}
