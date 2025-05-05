#ifndef DATE_H
#define DATE_H
#include <QDate>

class Date{
    public:
    Date();
    Date(int day,int month,int year);
    Date(QDate);
    bool operator>(Date);
    bool operator>=(Date);
    bool operator==(Date);
    bool operator>(QDate);
    bool operator>=(QDate);
    bool operator<=(QDate);
    bool setDay(int);
    bool setMonth(int);
    bool setYear(int);
    int getDay();
    int getMonth();
    int getYear();

    std::string toString();

    
    private:
    int day,month,year;
    friend bool isLeap(int year);
};

#endif

