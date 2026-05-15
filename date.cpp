#include <iostream>
using namespace std;

class Date
{
    private:
        int year;  // BC: negative; AD: positive
        int month; // can be 1~12
        int day;   // can be 1~28, 1~29, 1~30, 1~31

        int LegalDate_judge(int year_to_judge, int month_to_judge, int day_to_judge); // 0 for "ILLEGAL", 1 for "LEAGAL"
        int FirstDay_judge(); // 0 for "NOT first day"; 1 for "IS the first day of the month"; 2 for "IS the last day of the year";
        int LastDay_judge();   // 0 for "NOT last day"; 1 for "IS the last day of the month"; 2 for "IS the last day of the year"; 
        
        int Day_in_month(int Y, int M); // input Year/Month to get day numbers
    public:
        Date(): year(1), month(1), day(1){}
        Date(int Y_in, int M_in, int D_in);
        Date(const Date &date);
        ~Date() {}

        // operator reload
        Date &operator++();    // ++ Date
        Date operator++(int);  // Date ++; 

        Date &operator--();    // -- Date
        Date operator --(int); // Date --

        int LeapYear_judge(int year_to_judge) const; // 1 for "IS leap year"; 0 for "NOT leap year"; -1 for illegal input

        // date print: YYYY/MM/DD 
        void print() const;
};


/* ===================== construct funcion ========================= */

Date::Date(int Y_in, int M_in, int D_in)
{
    if (LegalDate_judge(Y_in, M_in, D_in) == 0)
    {
        Y_in = 1;
        M_in = 1;
        D_in = 1;

        cout << "ERROR! Date input illegal" << endl;
    }
    else
    {
        year = Y_in;
        month = M_in;
        day = D_in;
    }
}


Date::Date(const Date &date)
{
    if (LegalDate_judge(date.year, date.month, date.day) == 0)
    {
        year = 1;
        month = 1;
        day = 1;

        cout << "ERROR! Date input illegal" << endl;
    }
    else
    {
        year = date.year;
        month = date.month;
        day = date.day;
    }
}
/* ================================================================== */


/* ======================= privete judging function ===============================*/

int Date::Day_in_month(int Y, int M)
{
    switch (M)
    {
    /* month with 31 days */ 
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31; 
        break;
    /* month with 30 days */
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    /* Feb discussion*/
    default:
        if (this->LeapYear_judge(Y) == 1) // is leap year, Feb with 29 days
            return 29; 
        else // not leap year, Feb with 28 days
            return 28;
        break;
    }
}

int Date::LegalDate_judge(int year_to_judge, int month_to_judge, int day_to_judge)
{
    if (year_to_judge == 0) // year ILLEGAL
        return 0;
    else // year LEGAL
    {
        if (month_to_judge <1 || month_to_judge>12) // month ILLEGAL
            return 0;
        else // month legal
        {
            switch (month_to_judge)
            {
            /* month with 31 days */ 
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day_to_judge<1 || day_to_judge>31) 
                    return 0; // day illegal
                else           
                    return 1; // day legal
                break;
            /* month with 30 days */
            case 4:
            case 6:
            case 9:
            case 11:
                if (day_to_judge<1 || day_to_judge>30) 
                    return 0; // day illegal
                else           
                    return 1; // day legal
                break;
            /* Feb discussion*/
            default:
                if (this->LeapYear_judge(year_to_judge) == 1) // is leap year, Feb with 29 days
                    {
                    if (day_to_judge<1 || day_to_judge>29) 
                        return 0; // day illegal
                    else           
                        return 1; // day legal
                }
                else // not leap year, Feb with 28 days
                {
                    if (day_to_judge<1 || day_to_judge>28)
                        return 0; // day ILLEGAL
                    else 
                        return 1; // day LEGAL
                }
                break;
            }
        }
    }
}

int Date::FirstDay_judge()
{
    if (month == 1) 
    {
        if (day == 1) // Jan 1st
            return 2; // if --, year change
        else              
            return 0; // nothing change
    }
    else
    {
        if (day == 1)
            return 1;
        else 
            return 0;
    }
}

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
                return 0; // nothing change
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
                    return 0; // nothing change
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
/* =============================================================================== */


/* ============================= Date operating function ========================= */

void Date::print() const
{
    cout << year << "/" 
         << month << "/"
         << day << endl;
}
/* =============================================================================== */

/* ======================= public judging function ===============================*/

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
/* =============================================================================== */


/*============== operator reload ==============*/
Date &Date::operator++()
{
    if (this->LastDay_judge() == 2)
    {
        if (year == -1) // 1 BC
        {
            year = 1;   // 1 AD
            month = 1;
            day = 1;
        }
        else
        {
            year ++;
            month = 1;
            day = 1;
        }
    }
    else if (this->LastDay_judge() == 1) // last day of the month
    {
        // year remain unchanged
        month ++;
        day = 1;
    }
    else // ordinary day
        day ++;
    
    return *this;
}

Date Date::operator++(int)
{
    Date date_temp(*this);
    
    if (this->LastDay_judge() == 2)
    {
        if (year == -1) // 1 BC
        {
            year = 1;   // 1 AD
            month = 1;
            day = 1;
        }
        else
        {
            year ++;
            month = 1;
            day = 1;
        }
    }
    else if (this->LastDay_judge() == 1) // last day of the month
    {
        // year remain unchanged
        month ++;
        day = 1;
    }
    else // ordinary day
        day ++;

    // return original object
    return Date(date_temp);
}


Date &Date::operator--()
{
    if (this->FirstDay_judge() == 2) // first day of the year
    {
        if (year == 1) // 1 AD
        {
            year = -1;   // 1 BC
            month = 12;
            day = 31;
        }
        else
        {
            year --;
            month = 12;
            day = 31;
        }
    }
    else if (this->FirstDay_judge() == 1) // first day of the month
    {
        // year remain unchanged
        month --;
        day = this->Day_in_month(year, month - 1);
    }
    else // ordinary day
        day --;
    
    return *this;
}

Date Date::operator--(int)
{
    Date date_temp(*this);
    
    if (this->FirstDay_judge() == 2) // first day of the year
    {
        if (year == 1) // 1 AD
        {
            year = -1;   // 1 BC
            month = 12;
            day = 31;
        }
        else
        {
            year --;
            month = 12;
            day = 31;
        }
    }
    else if (this->FirstDay_judge() == 1) // first day of the month
    {
        // year remain unchanged
        month --;
        day = this->Day_in_month(year, month - 1);
    }
    else // ordinary day
        day --;

    return Date(date_temp);
}
/*=============================================*/



int main()
{
    Date d(2016, 1, 1);
    Date d_cpy1(d);
    Date d_cpy2(d);
    Date d_cpy3(d);
    Date d_cpy4(d);

    // ++ date test
    d.print();
    printf("\n");

    (++ d_cpy1).print();
    (d_cpy2 ++).print();
    d_cpy1.print();
    d_cpy2.print();
    printf("\n");

    (-- d_cpy3).print();
    (d_cpy4 --).print();
    d_cpy3.print();
    d_cpy4.print();

    return 0;
}