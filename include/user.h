#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <utility>
#include "date.h"
#include "resource.h"

using namespace std;

class User{
public:
    User();
    User (string username, string password, bool admin);
    int setUsername(string);

    /*
    0 : success
    -1: start with number
    -2 : non numeric and non alpha char
    -3 : exceeds 10 char
    -4 : existing
    -5: has uppercase
    */
    void setID(int id);
    string getUsername();
    int getId();
    int setPassword(string);
    /*
    0: success
    -1 : less than 4
    -2: more than 12
    -3 : doesn't contain numbers
    -4: no alpha
    -5 : special char other than : ?!;.@&%_-,
    */

    string getPassword();
    bool getAdmin();
    void setAdmin(bool);


    vector<BorrowedResource> borrowedResources;
    vector<pair<int,int>> indexOfReservedResources;
    static int currentId;




private:
    int id;
    string username;
    string password;
    bool isAdmin;
};

#endif
