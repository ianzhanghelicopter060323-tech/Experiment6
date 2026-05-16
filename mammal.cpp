#include <iostream>
#include <string>
using namespace std;


class Mammal_abstract
{
    protected:
        string name;
        int age;
    public:
        Mammal_abstract();
        Mammal_abstract(string name_in, int age_in);
        Mammal_abstract(const Mammal_abstract &m_in);
        virtual ~Mammal_abstract() {cout << "BASE CLASS deleted" << endl;}

        // output cry of the animal
        virtual void Speak() = 0 ;
};

class Mammal_normal
{
    protected:
        string name;
        int age;
    public:
        Mammal_normal();
        Mammal_normal(string name_in, int age_in);
        Mammal_normal(const Mammal_normal &m_in);
        virtual ~Mammal_normal() {cout << "BASE CLASS deleted" << endl;}

        // output cry of the animal
        virtual void Speak() 
        {    
            cout << "name: Do not know" << endl;
            cout << "age: Do not know" << endl;
            cout << "__DEFAULT CRY__" << endl; 
        }
};


class Cat_abstract : public Mammal_abstract
{
    public:
        Cat_abstract():Mammal_abstract() {}
        Cat_abstract(string name_in, int age_in): Mammal_abstract(name_in, age_in) {} 
        Cat_abstract(const Cat_abstract &c_in): Mammal_abstract(c_in) {}
        ~Cat_abstract() override {cout << "CAT CLASS deleted" << endl;}

        void Speak() override
        {
            cout << "name: " << name << endl;
            cout << "age: " << age << endl;
            cout << "Mew Mew" << endl;
        }
};

class Cat_normal : public Mammal_normal
{
    public:
        Cat_normal(): Mammal_normal() {}
        Cat_normal(string name_in, int age_in): Mammal_normal(name_in, age_in) {}
        Cat_normal(const Cat_normal &c_in): Mammal_normal(c_in) {}
        ~Cat_normal() override {cout << "CAT CLASS deleted" << endl;}

        void Speak() override
        {
            cout << "name: " << name << endl;
            cout << "age: " << age << endl;
            cout << "Mew Mew" << endl;
        }
};


class Dog_abstract : public Mammal_abstract
{
    public:
        Dog_abstract(): Mammal_abstract() {}
        Dog_abstract(string name_in, int age_in): Mammal_abstract(name_in, age_in) {} 
        Dog_abstract(const Dog_abstract &d_in): Mammal_abstract(d_in) {}
        ~Dog_abstract() override {cout << "DOG CLASS deleted" << endl;}

        void Speak() override
        {
            cout << "name: " << name << endl;
            cout << "age: " << age << endl;
            cout << "Woof Woof" << endl;
        }
};

class Dog_normal : public Mammal_normal
{
    public:
        Dog_normal(): Mammal_normal() {}
        Dog_normal(string name_in, int age_in): Mammal_normal(name_in, age_in) {}
        Dog_normal(const Dog_normal &d_in): Mammal_normal(d_in) {}
        ~Dog_normal() override {cout << "DOG CLASS deleted" << endl;}

        void Speak() override
        {
            cout << "name: " << name << endl;
            cout << "age: " << age << endl;
            cout << "Woof Woof" << endl;
        }
};


/* ====================== Mammal_abstract &Mammal_normal ====================== */

Mammal_abstract::Mammal_abstract()
{
    name = (string)" ";
    age = 0;
}

Mammal_normal::Mammal_normal()
{
    name = (string)" ";
    age = 0;
}


Mammal_abstract::Mammal_abstract(string name_in, int age_in)
{
    if (age_in < 0)
    {
        cout << "ERROR! input age should be positive" << endl;

        age_in = 0; // default age
    }

    name = name_in;
    age = age_in;
}

Mammal_normal::Mammal_normal(string name_in, int age_in)
{
    if (age_in < 0)
    {
        cout << "ERROR! input age should be positive" << endl;

        age_in = 0; // default age
    }

    name = name_in;
    age = age_in;
}


Mammal_abstract::Mammal_abstract(const Mammal_abstract &m_in)
{
    name = m_in.name;
    age = m_in.age;
}

Mammal_normal::Mammal_normal(const Mammal_normal &m_in)
{
    name = m_in.name;
    age = m_in.age;
}
/* ========================================================================== */


int main()
{
    // test Mammal_normal as a normal base class
    Mammal_normal *m_n[3];

    m_n[0] = new Mammal_normal((string)"GO", 4);
    m_n[1] = new Dog_normal((string)"Dahuang", 5);
    m_n[2] = new Cat_normal((string)"Xiaomiao", 3);

    cout << "normal base class test: " << endl;
    for (int i = 0; i < 3; i++)
    {
        m_n[i]->Speak();
        delete m_n[i];
    }
    cout << endl;


    // test Mammal_abstract as an abstract base class
    Mammal_abstract *m_a[2];

    // Mammal_abstract cannot create an object directly.
    // m_a[0] = new Mammal_abstract((string)"GO", 4);

    m_a[0] = new Dog_abstract((string)"Dahuang", 5);
    m_a[1] = new Cat_abstract((string)"Xiaomiao", 3);

    cout << "abstract base class test: " << endl;
    for (int i = 0; i < 2; i++)
    {
        m_a[i]->Speak();
        delete m_a[i];
    }
    cout << endl;

    return 0;
}
