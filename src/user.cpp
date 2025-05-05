#include "user.h"
#include "library.h"

int User :: currentId = 1;

User::User(){
    username = "user1";
    password = "password";
    id = currentId;
    currentId++;
}

User :: User(string user, string pass, bool admin){
    id = currentId;
    setUsername(user);
    setPassword(pass);
    isAdmin = admin;
    currentId++;
}


int User :: setUsername(string user){
    if (isdigit(user[0])) return -1;
    if (user.size()>10) return -3;
    for (int i=0; i < user.size();i++){
        if (isupper(user[i])) return -5;
    }
    for (int i =0; i <user.size();i++){
        if (!isdigit(user[i]) && !isalpha(user[i])) return -2;
    }
    if (Library::mainLibrary().libraryUsers.size()!=0){
        for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
            if (Library::mainLibrary().libraryUsers[i].getUsername() == user){
                return -4;
            }
        }
    }
    username= user;
    return 0;
}

string User :: getUsername(){
    return username;
}

int User :: getId(){
    return id;
}

string User :: getPassword(){
    return password;
}

int User::setPassword(string pass){
    if (pass.size() < 4) return -1;
    if (pass.size() > 12) return -2;
    bool checkNum = false, checkAlpha = false;
    for (int i =0; i<pass.size(); i++){
        if(isdigit(pass[i])) checkNum = true;
        if (isalpha(pass[i])) checkAlpha = true;
        if (!isdigit(pass[i]) && !isalpha(pass[i]) &&
            pass[i] != '?' && pass[i] != '!' && pass[i] != ';' && pass[i] != '.' &&
            pass[i] != '@' && pass[i] != '&' && pass[i] != '%' && pass[i] != '_' &&
            pass[i] != '-' && pass[i] != ','){
            return -5;
        }
        if (checkNum && checkAlpha) break;
    }
    if (!checkNum) return -3;
    if (!checkAlpha) return -4;
    password = pass;
    return 0;
}

bool User :: getAdmin(){
    return isAdmin;
}
void User :: setAdmin(bool admin){
    isAdmin = admin;
}


void User::setID(int id){
    this->id = id;
}
