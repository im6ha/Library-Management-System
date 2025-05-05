#ifndef LIBRARY_H
#define LIBRARY_H
#include "event.h"
#include "history.h"
#include "resource.h"
#include "user.h"
#include "date.h"
#include "helper.h"
#include "timee.h"
#include "email.h"
#include <QString>
#include <QMessageBox>


class Library{
public:
    static Library& mainLibrary();



    vector<vector<Resource>> libraryResources{4};
    //2D vector : 1st row:books, 2nd row:articles, 3rd row:digital content, 4th row: other

    list<User> libraryUsers;


    //ADDING/REMOVING
    pair<int,int> addResource(Resource r); //return (-1,-1) if success (resource not found)
    //else return index of existing resource and increment it
    int removeResource(pair<int,int>); //-2 :can't remove borrowed items, -1 id out of bound, -0: success

    //FINDING
    pair<int, int> findResource (Resource); //return (-1,-1) if resource not found
    Resource findResource(pair<int,int> id); //unique Resource
    vector <pair<int,int>> findResourceTitle(string title); //can have multiple resources
    vector <pair<int,int>> findResourcePublication (int publicationYear);
    vector <pair<int,int>> findResourceAuthor(string author);
    vector <pair<int,int>> findResourceType(string type);
    vector <pair<int,int>> findResourceKeyword(string keyword);//search in titles
    vector<pair<int,int>> findResourceKeywordAuthor(string keyword); //search in author names

    //EDITING

    bool editResource(pair<int,int>, Resource newResource,bool changeTitle,bool changeAuthor,
                      bool changeQuantity, bool changePublicationYear, bool changeType);

    //SORTING
    void sortTitle();
    void sortPublicationYear();
    void sortQuantity();
    void sortNumberOfReservations();
    void sortAuthor();
    vector<Resource> availabileResources();

    pair<int,int> login(string username, string password);
    pair<int,int> login (int id, string password);
    // 0 : sucess , -1: incorrect password, -2: username(/id) not found 1: admin
    void addUser(User);
    bool deleteUser(int id);
    bool deleteUser(string username);
    int findUser(int id);
    int findUser(string username);

    //BORROWING
    int borrowResource(User&,Resource&,Date, bool = true);
    int borrowResource(User&,pair<int,int>,Date, bool = true);
    // return 0 : success
    // return -1 : given id is out of range
    // return -2: same user trying to borow same resource before returning the first
    // return -3: not enough quantity
    bool returnResource(User&,Resource&,Date); //by default the date is set to the current date
    // checks if the resource is really borrowed by user
    void reserveResource(User&,Resource&); // if the resource isn't in library, it will be added as quantity =0
    bool deleteReservation(User&,Resource&);
    bool renewBorrow(User&,Resource,Date);
    // false if resource not borrowed, or renewed due date is less than previous one
    vector <User> borrowingUsers;
    vector <User> reservationUsers;

    //HISTORY OF BORROWS

    vector <History> borrowingHistory;

    static const vector <QString> errors; // to not rewrite error messages each time
    vector<Resource> oneD_libraryResources;//the sorted vector based on user
    int findBorrowedResource(User,Resource); //return index of borrowed resource in the borrowed resources vector of User
    int findReservation(User&,Resource&);

    Time openingTimes[7];
    Time closingTimes[7];
    bool isOpen[7];
    void setOpeningTimes(bool isOpenSunday, Time sundayOpening, Time sundayClosing,
                     bool isOpenMonday, Time mondayOpening, Time mondayClosing,
                     bool isOpenTuesday, Time tuesdayOpening, Time tuesdayClosing,
                     bool isOpenWednesday, Time wednesdayOpening, Time wednesdayClosing,
                     bool isOpenThursday, Time thursdayOpening, Time thursdayClosing,
                     bool isOpenFriday, Time fridayOpening, Time fridayClosing,
                     bool isOpenSaturday, Time saturdayOpening, Time saturdayClosing);


    //events
    vector <Event> libraryEvents;
    void refreshEvents(); //deletes old events (closing date<currentdate)
    int setEvent(string,string,Date,Time,Date,Time); //0= success, -1= available event with same title, -2= Dates and Times can't be less than current_time
    // -3 = closing date , time less than opening
    bool deleteEvent(string title);

    //emails
    vector<Email> libraryEmails;
    bool addEmail(Email);
    bool deleteEmail(Email);





private:

    bool editTitle(pair<int,int>, string newTitle);
    bool editAuthor(pair<int,int>, string newAuthor);
    bool editPublicationYear(pair<int,int>, int newPublicationYear);
    bool editQuantity(pair<int,int>, int newQuantity );
    bool editType(pair<int,int>, string newType);

    void setOneDLibraryResources();
};



#endif
