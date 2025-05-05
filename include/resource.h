#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <cctype>
#include <algorithm>
#include<vector>
#include "date.h"
using namespace std;

class Resource{
    public:
    Resource();
    Resource (string title, string author, int publicationYear, int quantity = 0,string type = "other");
    
    bool setTitle(string inputTitle);
    bool setAuthor(string);
    bool setPublicationYear(int);
    bool setQuantity(int);
    bool setAll(string inputTitle, string inputAuhtor, int publicationYear,int quantity=0, string type = "other");
    void setType(string);
    void setAvailability(bool);
    void setReservations(int);


    string getType();
    string getTitle();
    string getAuthor();
    int getPublicationYear();
    int getQuantity();
    bool getAvailability();
    int getReservations();

    bool operator==(Resource);
    bool operator!=(Resource);
    Resource operator+=(int);
    Resource operator-- ();
    pair<int,int> id;


    bool isBorrowed; //can't remove borrowed resources


    private:
    bool availability;
    string title;
    string author;
    int publicationYear;
    int quantity;
    string type;
    int reservations;


};

class BorrowedResource : public Resource{
public:
    BorrowedResource(Resource,Date,bool);
    Date dueDate;
    bool isPhysical;
};






#endif
