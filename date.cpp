#include <iostream>
using namespace std;

class Date
{
    private:
        int year;  // BC: negative; AD: positive
        int month; // can be 1~12
        int day;   // can be 1~28, 1~29, 1~30, 1~31

        // int LastDay_judge_month(); // 0 for "NOT last day"; 1 for "IS the last day of the month"; 2 for "IS the last day of the year"; 
    public:
        Date(): year(1), month(1), day(1){}
        Date(int Y_in, int M_in, int D_in): year(Y_in), month(M_in), day(D_in){};
        ~Date() {}

        int LastDay_judge();

        // operator reload
        Date &operator++();     // ++ Date
        Date &operator++(int);  // Date ++; 

        // 1 for "IS leap year"; 0 for "NOT leap year"; -1 for illegal input
        int LeapYear_judge(int year_to_judge) const;

};


int Date::LastDay_judge()
{
    if (month == 12)
    {
        if (day == 31) 
            return 2; // if ++, year change
        else           
            return 0; // nothing change
    }
    else
    {
        switch (month)
        {
        /* month with 31 days */ 
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        // case 12:
            if (day == 31) 
                return 1; // if ++, month cahnge
            else           
                return 1; // nothing change
            break;
        /* month with 30 days */
        case 4:
        case 6:
        case 9:
        case 11:
            if (day == 30) 
                return 1; // if ++, month cahnge
            else           
                return 0; //nothing change
            break;
        /* Feb discussion*/
        default:
            if (this->LeapYear_judge(year) == 1) // is leap year, Feb with 29 days
            {
                    if (day == 29)
                    return 1; // if ++, month change
                else 
                    return 2; // nothing change
            }
            else // not leap year, Feb with 28 days
            {
                if (day == 28)
                    return 1; // if ++, month change
                else 
                    return 0; // nothing change
            }
            break;
        }
    }
}


/*============== operator reload ==============*/
Date &Date::operator++()
{}

Date &Date::operator++(int)
{}
/*=============================================*/
int Date::LeapYear_judge(int year_to_judge) const
{
    if (year_to_judge == 0)
    {
        cout << "ERROR! year_to_judge cannot be 0" << endl;
        return -1;
    }

    // divisible by 400 is leap year
    // divisible by 4 is leap year.
    // divisible by 100 is not
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}


int main()
{
    /* Last day judge test
    Date d(2016, 1, 31);
    cout << d.LeapYear_judge(2016) << endl;
    cout << d.LastDay_judge() << endl;
    */
    return 0;
}