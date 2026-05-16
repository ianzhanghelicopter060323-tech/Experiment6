#include <iostream>
#include <string>

#define SALARY_PROF 5000
#define SALARY_ASSOPROF 3000
#define SALARY_LECTURER 2000

#define BONUS_PROF 50
#define BONUS_ASSOPROF 30
#define BONUS_LECTURER 20

using namespace std;


class Teacher
{
    protected:
        string name;
        int hours;
    public:
        Teacher(): name(" "), hours(0) {}
        Teacher(string name_in, int hours_in)
        {
            if (hours_in < 0) // illegal input judgement
            {
                cout << "ERROR! hours input should be non-negative" << endl;
                hours_in = 0;
            }

            name = name_in;
            hours = hours_in;
        }
        Teacher(const Teacher &t): name(t.name), hours(t.hours) {}
        virtual ~Teacher() {}

        virtual int Salary_calculate() const = 0;
        virtual void Infor_print() const = 0;
};

class Professor : public Teacher
{
    public:
        Professor(): Teacher() {}
        Professor(string name_in, int hours_in): Teacher(name_in, hours_in) {}
        Professor(const Professor &prof): Teacher(prof) {}
        ~Professor() {}

        int Salary_calculate() const override 
        {
            return SALARY_PROF + hours * BONUS_PROF;
        }

        void Infor_print() const override 
        {
            cout << "Name: " 
                 << name << endl;
            cout << "Title: "
                 << "Professor" << endl;
            cout << "hours: "
                 << hours << endl;
            cout << "Salary: "
                 << this->Salary_calculate() << endl;
        }
};

class AssociateProfessor : public Teacher
{
    public:
        AssociateProfessor(): Teacher() {}
        AssociateProfessor(string name_in, int hours_in): Teacher(name_in, hours_in) {}
        AssociateProfessor(const AssociateProfessor &prof): Teacher(prof) {}
        ~AssociateProfessor() {}

        int Salary_calculate() const override 
        {
            return SALARY_ASSOPROF + hours * BONUS_ASSOPROF;
        }

        void Infor_print() const override 
        {
            cout << "Name: " 
                 << name << endl;
            cout << "Title: "
                 << "Associate Professor" << endl;
            cout << "hours: "
                 << hours << endl;
            cout << "Salary: "
                 << this->Salary_calculate() << endl;
        }

};

class Lecturer : public Teacher
{
    public:
        Lecturer(): Teacher() {}
        Lecturer(string name_in, int hours_in): Teacher(name_in, hours_in) {}
        Lecturer(const Lecturer &prof): Teacher(prof) {}
        ~Lecturer() {}

        int Salary_calculate() const override 
        {
            return SALARY_LECTURER + hours * BONUS_LECTURER;
        }

        void Infor_print() const override 
        {
            cout << "Name: " 
                 << name << endl;
            cout << "Title: "
                 << "Lecturer" << endl;
            cout << "hours: "
                 << hours << endl;
            cout << "Salary: "
                 << this->Salary_calculate() << endl;
        }
};


int main()
{
    Teacher *TeaGroup[3];

    // Normal hours test
    cout << "Normal hours test:" << endl << endl;

    TeaGroup[0] = new Professor("Zhang", 20);
    TeaGroup[1] = new AssociateProfessor("Li", 18);
    TeaGroup[2] = new Lecturer("Wang", 16);

    for (int i = 0; i < 3; i++)
    {
        TeaGroup[i]->Infor_print();
        cout << endl;
        delete TeaGroup[i];
    }

    cout << endl;

    // Zero hours test
    cout << "Zero hours test:" << endl << endl;

    TeaGroup[0] = new Professor("Chen", 0);
    TeaGroup[1] = new AssociateProfessor("Liu", 0);
    TeaGroup[2] = new Lecturer("Zhao", 0);

    for (int i = 0; i < 3; i++)
    {
        TeaGroup[i]->Infor_print();
        cout << endl;
        delete TeaGroup[i];
    }

    cout << endl;

    // Negative hours input test
    cout << "Negative hours input test:" << endl << endl;

    TeaGroup[0] = new Professor("Sun", -5);
    TeaGroup[1] = new AssociateProfessor("Wu", -3);
    TeaGroup[2] = new Lecturer("Zhou", -1);

    for (int i = 0; i < 3; i++)
    {
        TeaGroup[i]->Infor_print();
        cout << endl;
        delete TeaGroup[i];
    }

    return 0;
}
