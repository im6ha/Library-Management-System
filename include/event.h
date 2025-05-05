#ifndef EVENT_H
#define EVENT_H
#include <string>
#include "date.h"
#include "timee.h"
using namespace std;

struct Event{
    Event(){};
    Event (string tit, string des, Date startD, Date endD, Time startT,Time endT) :
        title(tit), description(des),startingDate(startD),endingDate(endD),
        startingTime(startT),endingTime(endT){}
    string title;
    string description;
    Date startingDate;
    Date endingDate;
    Time startingTime;
    Time endingTime;
};

#endif
