#ifndef HISTORY_H
#define HISTORY_H

#include "user.h"
#include "resource.h"
struct History{
    History(){}
    History(User u, Resource r, Date d, bool b): borrowingUser(u), borrowedResource(r), returningDate(d), returnedOnTime(b){}
    User borrowingUser;
    Resource borrowedResource;
    Date returningDate;
    bool returnedOnTime;
};

#endif
