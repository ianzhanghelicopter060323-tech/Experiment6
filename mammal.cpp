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
        ~Cat_abstract() {cout << "CAT CLASS deleted" << endl;}

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
        ~Cat_normal() {cout << "CAT CLASS deleted" << endl;}

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
        ~Dog_abstract() {cout << "DOG CLASS deleted" << endl;}

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
        ~Dog_normal() {cout << "DOG CLASS deleted" << endl;}

        void Speak() override
        {
            cout << "name: " << name << endl;
            cout << "age: " << age << endl;
            cout << "Woof Woof" << endl;
        }
};


/* ====================== Mammal_abstract ====================== */

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
/* ============================================================= */


/* ====================== Cat_abstract ====================== */

/* ========================================================== */


/* ====================== Dog_abstract ====================== */
/* ========================================================== */


/* ====================== Mammal_normal ====================== */
/* =========================================================== */


/* ====================== Cat_normal ====================== */
/* ======================================================== */


/* ====================== Dog_normal ====================== */
/* ======================================================== */


int main()
{
    Mammal_normal *m_n_cat = new Cat_normal((string)"Maodie", 2);
    Mammal_normal *m_n_dog = new Dog_normal((string)"dagoujiao", 3);

    Mammal_abstract *m_a_cat = new Cat_abstract((string)"Laocai", 4);
    Mammal_abstract *m_a_dog = new Dog_abstract((string)"Xuangou", 6);

    m_n_cat->Speak();
    m_n_dog->Speak();
    cout << endl;

    m_a_cat->Speak();
    m_a_dog->Speak();
    cout << endl;

    // delete pointers
    delete m_n_cat;
    delete m_n_dog;

    delete m_a_cat;
    delete m_a_dog;
    return 0;
}
