#include "date.h"


Date::Date(int inputDay, int inputMonth, int inputYear) {
    setYear(inputYear);
    setMonth(inputMonth);
    setDay(inputDay);
}

Date :: Date(QDate d){
    year = d.year();
    setMonth(d.month());
    setDay(d.day());
}

Date :: Date(){
    year = 2025;
    month = 5;
    day = 1;
}

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::setDay(int inputDay) {
    int maxDays = 31;
    
    if (month == 4 || month == 6 || month == 9 || month == 11) maxDays = 30;
    else if (month == 2) maxDays = (isLeap(year)) ? 29 : 28;

    if (inputDay >= 1 && inputDay <= maxDays){
        day = inputDay;
        return true;
    }
    
    return false;
}

bool Date::setMonth(int inputMonth) {
    if (inputMonth >= 1 && inputMonth <= 12){
        month = inputMonth;
        return true;
    }
    
    return false;
}

int Date::getDay() {
    return day;
}

int Date::getMonth() {
    return month;
}



bool Date::operator>(Date d) {
    if (year != d.year) return year > d.year;
    if (month != d.month) return month > d.month;
    return day > d.day;    
}

bool Date :: operator>=(Date d){
    if ((*this > d) || (this->getDay() == d.getDay() && this->getMonth() == d.getMonth() && this->year == d.year)){
        return true;
    }
    return false;
}

bool Date::operator==(Date d){
    if (this->getDay() == d.getDay() && this->getMonth() == d.getMonth() && this->year == d.year){
        return true;
    }
    return false;
}

bool Date :: operator>(QDate d){
    if (year != d.year()) return year > d.year();
    if (month != d.month()) return month > d.month();
    return day > d.day();
}

bool Date :: operator>=(QDate d){
    if ((*this > d) || (this->getDay() == d.day() && this->getMonth() == d.month() && this->year == d.year())){
        return true;
    }
    return false;
}

bool Date::operator<=(QDate d){
    return !((*this)>d);
}

std::string Date::toString(){
    std::string SDay = std::to_string(this->getDay()), SMonth = std::to_string(this->getMonth()), SYear = std::to_string(this->year);
    return SDay+"/"+SMonth+"/"+SYear;
}


int Date :: getYear(){
    return year;
}

bool Date :: setYear(int y){
    if (y<0) return false;
    year = y;
    return true;
}
