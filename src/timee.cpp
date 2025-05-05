#include "timee.h"

Time::Time(int h,int m){
    setHours(h);
    setMinutes(m);
}

Time::Time(QTime t){
    setAll(t.hour(),t.minute());
}

Time::Time(){
}

void Time :: setAll(int h,int m){
    setHours(h);
    setMinutes(m);
}


void Time :: setHours(int h){
    if (h >=0 && h < 24){
        hours = h;
        return;
    }
    hours =0;
}

void Time :: setMinutes(int m){
    if (m<0) {
        m =0;
        return;
    }
    //m>=0
    if (m<60) {
        minutes = m;
        return;
    }
    //m>=60
    minutes = m%60;
    setHours(hours+(m/60));
}


int Time ::getHours(){
    return hours;
}


int Time :: getMinutes(){
    return minutes;
}

bool Time::operator>(Time t){
    //this>t
    if (this->hours != t.hours){
        return (this->hours > t.hours);
    }
    
    if (this->minutes != t.minutes){
        return (this->minutes > t.minutes);
    }
    return false;
}

bool Time::operator==(Time t){
    return this->hours == t.hours && this->minutes == t.minutes ;
}

bool Time::operator>=(Time t){
    return (*this) > t || (*this)==t;

}


bool Time::operator>(QTime t){
    //this>t
    if (this->hours != t.hour()){
        return (this->hours > t.hour());
    }

    if (this->minutes != t.minute()){
        return (this->minutes > t.minute());
    }
return false;
}


bool Time::operator>=(QTime t){
    return (*this) > t || (*this)==t;

}

bool Time :: operator<=(QTime t){
    return !((*this)>t);
}

Time Time::operator-(Time t){
    Time result(0,0);
    Time copy(this->getHours(),this->getMinutes());

    if(t>=*this) return result;

    if(t.getMinutes()>this->getMinutes()){
        copy.setMinutes(copy.getMinutes()+60);
        copy.setHours(copy.getHours()-1);
    }
    result.setHours(copy.getHours()-t.getHours());
    result.setMinutes(copy.getMinutes()-t.getMinutes());
    return result;

}

string Time::toString(){
    string hour,minute;
    if (this->getHours()<10)
        hour = "0"+ to_string(this->getHours());
    else
        hour = to_string(this->getHours());
    if (this->getMinutes()<10)
        minute = "0"+ to_string(this->getMinutes());
    else
        minute = to_string(this->getMinutes());

    return hour + ":" + minute;
}

string Time:: toStringAMPM(){
    string hour,minute;
    string ampm="AM";
    Time copy(this->getHours(),this->getMinutes());
    if(copy.getHours()>12){
        ampm="PM";
        copy.setHours(this->getHours()%12);
    }
    if (copy.getHours()<10)
        hour = "0"+ to_string(copy.getHours());
    else
        hour = to_string(copy.getHours());
    if (copy.getMinutes()<10)
        minute = "0"+ to_string(copy.getMinutes());
    else
        minute = to_string(copy.getMinutes());

    return hour + ":" + minute + ampm;

}

