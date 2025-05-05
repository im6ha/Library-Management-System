#ifndef HELPER_H
#define HELPER_H
#include "user.h"
#include "resource.h"
#include <QString>
#include <QWidget>
#include <QMessageBox>




class Helper {
public:

    static void sortbyQuantity(vector<Resource>& vec); //std::sort
    static void sortbyPublicationYear(vector<Resource>& vec); 
    static void sortReservation(vector<Resource>& vec);
    static void sortbyTitle(vector<Resource>& vec);
    static void sortbyAuthor(vector<Resource>& vec);
    static int setRowIndex(string type);
    static vector <pair<int,int>> intersection(vector<pair<int,int>> v1, vector<pair<int,int>> v2,
                                        vector<pair<int,int>> v3,vector<pair<int,int>> v4);

    static void reverse(vector<Resource>&);
    static bool confirmAction(QWidget*);

    static void save();
    static void load();
    static bool sendEmail(QString recipient, QString subject,QString text);
    static void sendEmailToAll(QString subject,QString text);



private:
    static vector<string> splitString(string, char);
    static void saveLibraryResources();
    static void saveUsers();
    static void saveBorrowingUsers();
    static void saveReservationUsers();
    static void saveBorrowingHistory();
    static void saveLibraryEvents();
    static void saveOpeningSchedule();
    static void saveEmails();


    static void loadLibraryResources();
    static void loadUsers();
    static void loadBorrowingUsers();
    static void loadReservationUsers();
    static void loadBorrowingHistory();
    static void loadLibraryEvents();
    static void loadOpeningSchedule();
    static void loadEmails();

    static void saveUserData(string file, vector<User> vector);
    static void loadUserData(string file, vector<User> &vector);







};

#endif // HELPER_H
