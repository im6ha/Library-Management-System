#ifndef EMAIL_H
#define EMAIL_H
#include <string>
#include "helper.h"
using namespace std;

class Email{
    public:
    Email(string e){
        setEmail(e);
    }

    string getEmail(){
        return email;
    }

    bool setEmail(string email){
        if(!checkEmail(email)){
            email = "default@email.dz";
            return false;
        }
        this->email = email;
        return true;
    }

    static bool checkEmail(string email){
        int indexOfAtSymbol = email.find_first_of('@');
        if(indexOfAtSymbol == string::npos) return false;
        string firstPart = email.substr(0,indexOfAtSymbol), secondPart = email.substr(indexOfAtSymbol+1);
        for (char c : secondPart){
            if(!isalpha(c) && c !='.') return false;
        }
        for (char c : firstPart){
            if(!isalpha(c) && !isdigit(c) && c!='.') return false;
        }
        return true;
    }

    private:
    string email;

};

#endif
