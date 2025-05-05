#ifndef TIMEE_H
#define TIMEE_H
#include <string>
#include <QTime>
using namespace std;
class Time{ //no need for sec
    public:
    Time();
    Time(int,int);
    Time(QTime);
    void setAll(int,int);
    void setHours(int);
    void setMinutes(int);
    int getHours();
    int getMinutes();
    bool operator>(Time);
    bool operator>=(Time);
    bool operator==(Time);
    bool operator>(QTime);
    bool operator>=(QTime);
    bool operator<=(QTime);
    Time operator-(Time);

    string toString();
    string toStringAMPM();

    private:
    int hours,minutes;
};

#endif
