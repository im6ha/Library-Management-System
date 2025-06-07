#include "helper.h"
#include "library.h"
#include <fstream>
#include <algorithm>
#include "qdir.h"
#include "smtp/src/smtpclient.h"
#include "smtp/src/mimemessage.h"
#include "smtp/src/mimetext.h"
#include "smtp/src/emailaddress.h"



void Helper :: sortbyQuantity(vector<Resource>& vec){ 
    sort(vec.begin(), vec.end(), [](Resource r1, Resource r2){
        return r2.getQuantity() < r1.getQuantity(); // descending order
    });
}

void Helper :: sortbyPublicationYear(vector<Resource>& vec){ 
    sort(vec.begin(), vec.end(), [](Resource r1, Resource r2){
        return r2.getPublicationYear() < r1.getPublicationYear(); // descending order
    });
}


void Helper :: sortReservation(vector<Resource>& vec){
    sort(vec.begin(), vec.end(), [](Resource r1, Resource r2){
        return r2.getReservations() < r1.getReservations(); // descending order
    });
}


void Helper :: sortbyTitle(vector<Resource>& vec){
    sort(vec.begin(), vec.end(), [](Resource r1, Resource r2){
        return r2.getTitle() > r1.getTitle(); // ascending order
    });
}

void Helper :: sortbyAuthor(vector<Resource>& vec){
    sort(vec.begin(), vec.end(), [](Resource r1, Resource r2){
        return r2.getAuthor() > r1.getAuthor(); // ascending order
    });
}

void Helper:: reverse(vector<Resource>& vec) {
    std :: reverse(vec.begin(), vec.end());
}


vector<pair<int, int>> Helper::  intersection(vector<pair<int,int>> v1, vector<pair<int,int>> v2, vector<pair<int,int>> v3,vector<pair<int,int>> v4)
{
    vector<pair<int, int>> result1, result2, result3;
    pair<int,int> defaultVal = make_pair(-2,-2);

    if (!v1.empty() && !v2.empty() && !v3.empty() && !v4.empty()) {
        if(v1[0] == defaultVal && v2[0] == defaultVal && v3[0] == defaultVal && v4[0] != defaultVal){
            return v4;
        }
        else if(v1[0] == defaultVal && v2[0] == defaultVal && v3[0] != defaultVal && v4[0] == defaultVal){
            return v3;
        }
        else if(v1[0] == defaultVal && v2[0] != defaultVal && v3[0] == defaultVal && v4[0] == defaultVal){
            return v2;
        }
        else if(v1[0] != defaultVal && v2[0] == defaultVal && v3[0] == defaultVal && v4[0] == defaultVal){
            return v1;
        }
    }

    if (!v1.empty() && v1.size() == 1 && v1[0] == defaultVal && !v2.empty() && v2[0] != defaultVal){
        result1 = v2;
    }
    if (!v2.empty() && v2.size() == 1 && v2[0] == defaultVal && !v1.empty() && v1[0] != defaultVal){
        result1 = v1;
    }

    if (!v1.empty() && !v2.empty() && v1.size()== 1 && v2.size() == 1 && v1[0] == defaultVal && v2[0] == defaultVal){
        v1 = v3;
        v2 = v4;
        v3.clear();
        v4.clear();
        v3.push_back(defaultVal);
        v4.push_back(defaultVal);
    }

    if ((v1.empty() || v1.size() == 1 && v1[0] == make_pair(-1, -1)) ||
        (v2.empty() || v2.size() == 1 && v2[0] == make_pair(-1, -1))) {
        return {make_pair(-1, -1)};
    }

    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            if (v1[i] == v2[j]) result1.push_back(v1[i]);
        }
    }
    if (result1.empty()) return {make_pair(-1, -1)};

    if (!v3.empty() && !v4.empty()) {
        for (int i = 0; i < v3.size(); i++) {
            for (int j = 0; j < v4.size(); j++) {
                if (v3[i] == v4[j]) result2.push_back(v3[i]);
            }
        }
    }
    if (result2.empty()) return {make_pair(-1, -1)};

    for (int i = 0; i < result1.size(); i++) {
        for (int j = 0; j < result2.size(); j++) {
            if (result1[i] == result2[j]) result3.push_back(result2[i]);
        }
    }
    if (result3.empty()) return {make_pair(-1, -1)};

    vector<pair<int, int>> finalResult;
    for (int i = 0; i < result3.size(); i++) {
        if (result3[i] != defaultVal) {
            finalResult.push_back(result3[i]);
        }
    }
    return finalResult;
}




int Helper :: setRowIndex(string type){
    if (type== "Book"||type == "book") return 0;
    else if (type == "Article" || type == "article") return 1;
    else if (type == "Digital Content" || type == "digital content") return 2;
    else return 3;
}

bool Helper:: confirmAction(QWidget *parent) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(parent, "Confirmation", "Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No);
    return (reply == QMessageBox::Yes);
}


void Helper::saveLibraryResources() {
    ofstream saveLibraryResourcesCSV("../data/libraryResources.csv");
    saveLibraryResourcesCSV << "ID1,ID2,Type,Title,Author,PublicationYear,Quantity,Availability,isBorrowed,Reservations\n";
    for (int i=0; i<4; i++){
        for (Resource r : Library::mainLibrary().libraryResources[i]){
            saveLibraryResourcesCSV << r.id.first << ",";
            saveLibraryResourcesCSV << r.id.second << ",";
            saveLibraryResourcesCSV << r.getType() << ",";
            saveLibraryResourcesCSV << r.getTitle() << ",";
            saveLibraryResourcesCSV <<r.getAuthor() << ",";
            saveLibraryResourcesCSV << r.getPublicationYear() << ",";
            saveLibraryResourcesCSV << r.getQuantity() << ",";
            saveLibraryResourcesCSV << r.getAvailability() << ",";
            saveLibraryResourcesCSV << r.isBorrowed << ",";
            saveLibraryResourcesCSV << r.getReservations() << "\n";
        }
    }
    saveLibraryResourcesCSV.close();
}

void Helper::saveUserData(string file, vector<User> vector){
    ofstream saveUsersCSV(file);
    saveUsersCSV << "id,username,isAdmin,password,indexOfReservedResource1,indexOfReservedResource2,"
                    "indexOfBorrowedResource1,indexOfBorrowedResource2,dueDay,dueMonth,dueYear,isPhysical\n";

    for(User u : vector){
        saveUsersCSV << u.getId() << ",";
        saveUsersCSV << u.getUsername() << ",";
        saveUsersCSV<<u.getAdmin() << ",";
        saveUsersCSV << u.getPassword() << ",";
        if(u.indexOfReservedResources.empty()){
            saveUsersCSV << ",,";
        }
        else{
            for (int i=0; i < u.indexOfReservedResources.size(); i++){
                if (i != u.indexOfReservedResources.size() -1){
                    saveUsersCSV << u.indexOfReservedResources[i].first << " ";
                }
                else saveUsersCSV << u.indexOfReservedResources[i].first << ",";
            }
            for (int i=0; i < u.indexOfReservedResources.size(); i++){
                if (i != u.indexOfReservedResources.size() -1){
                    saveUsersCSV << u.indexOfReservedResources[i].second << " ";
                }
                else saveUsersCSV << u.indexOfReservedResources[i].second << ",";
            }
        }

        if (u.borrowedResources.empty()){
            saveUsersCSV<<",,,,,,";
        }

        else{

            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].id.first << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].id.first << ",";
            }
            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].id.second << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].id.second << ",";
            }

            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].dueDate.getDay() << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].dueDate.getDay() << ",";
            }
            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].dueDate.getMonth() << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].dueDate.getMonth() << ",";
            }

            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].dueDate.getYear() << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].dueDate.getYear() << ",";
            }

            for (int i=0; i < u.borrowedResources.size(); i++){
                if (i != u.borrowedResources.size() -1){
                    saveUsersCSV << u.borrowedResources[i].isPhysical << " ";
                }
                else saveUsersCSV << u.borrowedResources[i].isPhysical << ",";
            }
        }
        saveUsersCSV << "\n";
    }

    saveUsersCSV.close();
}
void Helper::saveUsers() {
    Helper::saveUserData("../data/users.csv", Library::mainLibrary().libraryUsers);
}

void Helper::saveBorrowingHistory() {
        ofstream saveBorrowingHistoryCSV("../data/borrowingHistory.csv");
        saveBorrowingHistoryCSV << "UserID,username,isAdmin,password,indexOfReservedResource1,indexOfReservedResource2,"
                                   "indexOfBorrowedResource1,indexOfBorrowedResource2,dueDay,dueMonth,dueYear,"
                                   "isPhysical,ResourceID1,ResourceID2,type,title,author,publicationYear,quantity,availability,"
                                   "isBorrowed,numberOfReservations,returningDay,returningMonth,returningYear,"
                                   "returnedOnTime\n";

        for (History historyIns : Library::mainLibrary().borrowingHistory){
            saveBorrowingHistoryCSV << historyIns.borrowingUser.getId() << ",";
            saveBorrowingHistoryCSV << historyIns.borrowingUser.getUsername()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowingUser.getAdmin()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowingUser.getPassword()<< ",";

            if(historyIns.borrowingUser.indexOfReservedResources.empty()){
                saveBorrowingHistoryCSV <<",,";
            }
            else{
            for (int i=0; i < historyIns.borrowingUser.indexOfReservedResources.size(); i++){
                if (i != historyIns.borrowingUser.indexOfReservedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.indexOfReservedResources[i].first << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.indexOfReservedResources[i].first << ",";
            }
            for (int i=0; i < historyIns.borrowingUser.indexOfReservedResources.size(); i++){
                if (i != historyIns.borrowingUser.indexOfReservedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.indexOfReservedResources[i].second << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.indexOfReservedResources[i].second << ",";
            }
            }

            if(historyIns.borrowingUser.borrowedResources.empty()){
                saveBorrowingHistoryCSV <<",,";
            }
            else{

            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].id.first << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].id.first << ",";
            }
            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].id.second << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].id.second << ",";
            }
            }

            if(historyIns.borrowingUser.borrowedResources.empty()){
                saveBorrowingHistoryCSV <<",,,";
            }
            else{

            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getDay() << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getDay() << ",";
            }
            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getMonth() << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getMonth() << ",";
            }

            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getYear() << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].dueDate.getYear() << ",";
            }
            }

            if(historyIns.borrowingUser.borrowedResources.empty()){
                saveBorrowingHistoryCSV <<",";
            }
            else{

            for (int i=0; i < historyIns.borrowingUser.borrowedResources.size(); i++){
                if (i != historyIns.borrowingUser.borrowedResources.size() -1){
                    saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].isPhysical << " ";
                }
                else saveBorrowingHistoryCSV << historyIns.borrowingUser.borrowedResources[i].isPhysical << ",";
            }
            }
            saveBorrowingHistoryCSV << historyIns.borrowedResource.id.first<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.id.second<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getType()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getTitle()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getAuthor()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getPublicationYear()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getQuantity()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getAvailability()<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.isBorrowed<< ",";
            saveBorrowingHistoryCSV << historyIns.borrowedResource.getReservations()<< ",";
            saveBorrowingHistoryCSV << historyIns.returningDate.getDay()<< ",";
            saveBorrowingHistoryCSV << historyIns.returningDate.getMonth()<< ",";
            saveBorrowingHistoryCSV << historyIns.returningDate.getYear()<< ",";
            saveBorrowingHistoryCSV << historyIns.returnedOnTime<< "\n";
        }

        saveBorrowingHistoryCSV.close();
    }

    void Helper::saveLibraryEvents() {
        ofstream saveLibraryEventsCSV("../data/libraryEvents.csv");
        saveLibraryEventsCSV << "Title,Description,StartDay,StartMonth,StartYear,StartHour,StartMinute,"
                                "EndDay,EndMonth,EndYear,EndHour,EndMinute\n";

        for (Event event : Library::mainLibrary().libraryEvents){
            saveLibraryEventsCSV<<event.title << ",";
            saveLibraryEventsCSV<<event.description << ",";
            saveLibraryEventsCSV<<event.startingDate.getDay() << ",";
            saveLibraryEventsCSV<<event.startingDate.getMonth() << ",";
            saveLibraryEventsCSV<<event.startingDate.getYear() << ",";
            saveLibraryEventsCSV<<event.startingTime.getHours() << ",";
            saveLibraryEventsCSV<<event.startingTime.getMinutes() << ",";
            saveLibraryEventsCSV<<event.endingDate.getDay() << ",";
            saveLibraryEventsCSV<<event.endingDate.getMonth() << ",";
            saveLibraryEventsCSV<<event.endingDate.getYear() << ",";
            saveLibraryEventsCSV<<event.endingTime.getHours() << ",";
            saveLibraryEventsCSV<<event.endingTime.getMinutes() << "\n";
        }
        saveLibraryEventsCSV.close();
    }

void Helper::saveOpeningSchedule() {

        ofstream saveOpeningScheduleCSV("../data/openingSchedule.csv");
        saveOpeningScheduleCSV << "OpenHour,OpenMinute,CloseHour,CloseMinute,IsOpen\n";
        for (int i=0; i < 7; i++){
            saveOpeningScheduleCSV << Library::mainLibrary().openingTimes[i].getHours() << ",";
            saveOpeningScheduleCSV << Library::mainLibrary().openingTimes[i].getMinutes()<< ",";
            saveOpeningScheduleCSV << Library::mainLibrary().closingTimes[i].getHours()<< ",";
            saveOpeningScheduleCSV << Library::mainLibrary().closingTimes[i].getMinutes()<< ",";
            saveOpeningScheduleCSV << Library::mainLibrary().isOpen[i]<< "\n";
        }
        saveOpeningScheduleCSV.close();
    }

void Helper::saveBorrowingUsers() {
    Helper::saveUserData("../data/borrowingUsers.csv", Library::mainLibrary().borrowingUsers);
}

void Helper::saveReservationUsers() {
    Helper::saveUserData("../data/reservationUsers.csv",Library::mainLibrary().reservationUsers);
}

void Helper::saveEmails(){
    ofstream libraryEmailsCSV("../data/emails.csv");

    for (Email email : Library::mainLibrary().libraryEmails){
        libraryEmailsCSV << email.getEmail() <<"\n";

    }
    libraryEmailsCSV.close();
}



vector<string> Helper :: splitString(string line, char del) {
    vector<string> words;
    string word;
    int currentWordIndex = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == del) {
            words.push_back(line.substr(currentWordIndex, i - currentWordIndex));
            currentWordIndex = i + 1;
        }
    }

    words.push_back(line.substr(currentWordIndex));

    return words;
}

void Helper::loadBorrowingHistory(){
    string line;
    vector<string> fields;
    ifstream borrowingHistoryCSV("../data/borrowingHistory.csv");
    Library::mainLibrary().borrowingHistory.clear();
    if (borrowingHistoryCSV) {
        getline(borrowingHistoryCSV, line); // skip header
        while (getline(borrowingHistoryCSV, line) && line.find_first_not_of(' ') != std::string::npos) {
            fields = splitString(line, ',');
            int id = stoi (fields[0]);
            string username = fields[1];
            bool isAdmin = stoi(fields[2]);
            string password = fields[3];

            vector <pair<int,int>> indexOfReservedResources;
            vector <string> indexOfReservedResources1STR = splitString(fields[4], ' '),
                indexOfReservedResources2STR = splitString(fields[5], ' ');
            for (int i = 0; i < indexOfReservedResources1STR.size(); i++){
                indexOfReservedResources.push_back(make_pair(stoi(indexOfReservedResources1STR[i]) ,
                                                             stoi(indexOfReservedResources2STR[i]) ));
            }

            vector <pair<int,int>> indexOfBorrowedResources;
            vector <string> indexOfBorrowedResources1STR = splitString(fields[6], ' '),
                indexOfBorrowedResources2STR = splitString(fields[7], ' ');
            for (int i = 0; i < indexOfBorrowedResources.size(); i++){
                indexOfBorrowedResources.push_back(make_pair(stoi(indexOfBorrowedResources1STR[i]),
                                                             stoi(indexOfBorrowedResources2STR[i])));
            }

            vector<Date> dueDates;
            vector<string> dueDaySTR = splitString(fields[8], ' '),
                dueMonthSTR = splitString(fields[9], ' '),dueYearSTR = splitString(fields[10], ' ');
            for (int i=0; i < dueDaySTR.size(); i++){
                dueDates.push_back(Date(stoi(dueDaySTR[i]), stoi(dueMonthSTR[i]), stoi(dueYearSTR[i])));
            }
            vector<string> isPhysicalSTR = splitString(fields[11], ' ');
            vector<bool> isPhysical;

            for (int i=0; i < isPhysicalSTR.size(); i++){
                isPhysical.push_back(stoi(isPhysicalSTR[i]));
            }

            int id1 = stoi(fields[12]);
            int id2 = stoi(fields[13]);
            string type = fields[14];
            string title = fields[15];
            string author = fields[16];
            int publicationYear = stoi(fields[17]);
            int quantity  = stoi(fields[18]);
            bool availability = stoi(fields[19]);
            bool isBorrowed = stoi(fields[20]);
            int numberOfReservations = stoi(fields[21]);

            Date d(stoi(fields[22]), stoi(fields[23]), stoi(fields[24]));
            bool onTime = stoi(fields[25]);

            Resource r(title, author, publicationYear, quantity, type);
            r.id = make_pair(id1, id2);
            r.setAvailability(availability);
            r.isBorrowed   = isBorrowed;
            r.setReservations(numberOfReservations);

            User u(username,password,isAdmin);
            u.setID(id);
            u.indexOfReservedResources = indexOfReservedResources;
            for (int i=0; i < indexOfBorrowedResources.size(); i++){
                u.borrowedResources[i] = BorrowedResource(Library::mainLibrary().findResource(indexOfBorrowedResources[i])
                                                          ,dueDates[i],isPhysical[i]) ;
            }

            History h(u,r,d,onTime);
            Library::mainLibrary().borrowingHistory.push_back(h);


        }
        borrowingHistoryCSV.close();
    }
}

void Helper::loadUserData(string file, vector<User> &vec){
    string line;
    vector<string> fields;
    ifstream usersCSV(file);
    Library::mainLibrary().borrowingUsers.clear();
    if (usersCSV) {
        getline(usersCSV, line); // skip header
        while (getline(usersCSV, line)&& line.find_first_not_of(' ') != std::string::npos) {
            fields = splitString(line, ',');
            int id = stoi (fields[0]);
            string username = fields[1];
            bool isAdmin = stoi(fields[2]);
            string password = fields[3];

            vector <pair<int,int>> indexOfReservedResources;
            vector <string> indexOfReservedResources1STR = splitString(fields[4], ' '),
                indexOfReservedResources2STR = splitString(fields[5], ' ');
            if (!(indexOfReservedResources1STR.size()==1 && indexOfReservedResources1STR[0] == "")){
                for (int i = 0; i < indexOfReservedResources.size(); i++){
                    indexOfReservedResources.push_back(make_pair(stoi(indexOfReservedResources1STR[i]) ,
                                                                 stoi(indexOfReservedResources2STR[i]) ));
                }
            }

            vector <pair<int,int>> indexOfBorrowedResources;
            vector <string> indexOfBorrowedResources1STR = splitString(fields[6], ' '),
                indexOfBorrowedResources2STR = splitString(fields[7], ' ');
            if (!(indexOfBorrowedResources1STR.size()==1 && indexOfBorrowedResources1STR[0] == "")){
                for (int i = 0; i < indexOfBorrowedResources.size(); i++){
                    indexOfBorrowedResources.push_back(make_pair(stoi(indexOfBorrowedResources1STR[i]),
                                                                 stoi(indexOfBorrowedResources2STR[i])));
                }
            }

            vector<Date> dueDates;
            vector<string> dueDaySTR = splitString(fields[8], ' '),
                dueMonthSTR = splitString(fields[9], ' '),dueYearSTR = splitString(fields[10], ' ');
            if (!(dueDaySTR.size()==1 && dueDaySTR[0] == "")){
                for (int i=0; i < dueDaySTR.size(); i++){
                    dueDates.push_back(Date(stoi(dueDaySTR[i]), stoi(dueMonthSTR[i]), stoi(dueYearSTR[i])));
                }
            }
            vector<string> isPhysicalSTR = splitString(fields[11], ' ');
            vector<bool> isPhysical;

            if (!(isPhysicalSTR.size()==1 && isPhysicalSTR[0] == "")){
                for (int i=0; i < isPhysicalSTR.size(); i++){
                    isPhysical.push_back(stoi(isPhysicalSTR[i]));
                }
            }

            User u(username,password,isAdmin);
            u.setID(id);
            u.indexOfReservedResources = indexOfReservedResources;
            for (int i=0; i < indexOfBorrowedResources.size(); i++){
                u.borrowedResources[i] = BorrowedResource(Library::mainLibrary().findResource(indexOfBorrowedResources[i])
                                                          ,dueDates[i],isPhysical[i]) ;
            }
            vec.push_back(u);


        }
        usersCSV.close();
    }
}

void Helper::loadBorrowingUsers(){
    loadUserData("../data/borrowingUsers.csv", Library::mainLibrary().borrowingUsers);
}

void Helper::loadLibraryResources(){
    string line;
    vector<string> fields;
    ifstream libraryResourcesCSV("../data/libraryResources.csv");
    Library::mainLibrary().libraryResources.clear();
    if (libraryResourcesCSV) {
        getline(libraryResourcesCSV, line); // skip header
        while (getline(libraryResourcesCSV, line) && line.find_first_not_of(' ') != std::string::npos) {
            fields = splitString(line, ',');
            int id1 = stoi(fields[0]);
            int id2 = stoi(fields[1]);
            string type = fields[2];
            string title = fields[3];
            string author = fields[4];
            int publicationYear = stoi(fields[5]);
            int quantity  = stoi(fields[6]);
            bool availability = stoi(fields[7]);
            bool isBorrowed = stoi(fields[8]);
            int numberOfReservations = stoi(fields[9]);

            Resource r(title, author, publicationYear, quantity, type);
            r.id = make_pair(id1, id2);
            r.setAvailability(availability);
            r.isBorrowed   = isBorrowed;
            r.setReservations(numberOfReservations);

            Library::mainLibrary().libraryResources[setRowIndex(type)].push_back(r);
        }
        libraryResourcesCSV.close();
    }

}

void Helper :: loadUsers(){
    loadUserData("../data/users.csv", Library::mainLibrary().libraryUsers);
}

void Helper::loadOpeningSchedule(){
    string line;
    vector<string> fields;
    ifstream openingScheduleCSV("../data/openingSchedule.csv");
    if (openingScheduleCSV) {
        getline(openingScheduleCSV, line); // skip header
        for(int i=0; i < 7; i++) {
            if (!getline(openingScheduleCSV, line)) break;
            fields = splitString(line, ',');
            Library::mainLibrary().openingTimes[i] = Time(stoi(fields[0]), stoi(fields[1]));
            Library::mainLibrary().closingTimes[i] = Time(stoi(fields[2]), stoi(fields[3]));
            Library::mainLibrary().isOpen[i] = stoi(fields[4]);
        }
        openingScheduleCSV.close();
    }
}

void Helper::loadReservationUsers(){
    loadUserData("../data/reservationUsers.csv",Library::mainLibrary().reservationUsers);
}

void Helper::loadLibraryEvents(){
    string line;
    vector<string> fields;

    ifstream libraryEventsCSV("../data/libraryEvents.csv");
    Library::mainLibrary().libraryEvents.clear();
    if (libraryEventsCSV) {
        getline(libraryEventsCSV, line); // skip header
        while (getline(libraryEventsCSV, line) && line.find_first_not_of(' ') != std::string::npos) {
            fields = splitString(line, ',');

            string title = fields[0];
            string description = fields[1];
            Date startingDate(stoi(fields[2]), stoi(fields[3]), stoi(fields[4]));
            Time startingTime(stoi(fields[5]),stoi(fields[6]));
            Date endingDate(stoi(fields[7]),stoi(fields[8]),stoi(fields[9]));
            Time endingTime(stoi(fields[10]),stoi(fields[11]));

            Event event(title,description,startingDate,endingDate,startingTime,endingTime);
            Library::mainLibrary().libraryEvents.push_back(event);

        }
        libraryEventsCSV.close();
    }
}

void Helper::loadEmails(){
    string line;
    ifstream libraryEmailsCSV("../data/emails.csv");
    Library::mainLibrary().libraryEmails.clear();
    if (libraryEmailsCSV) {
        while (getline(libraryEmailsCSV, line) && line.find_first_not_of(' ') != std::string::npos) {
            Email email(line);
            Library::mainLibrary().libraryEmails.push_back(email);
        }
        libraryEmailsCSV.close();
    }
}


void Helper::save(){
    Helper::saveBorrowingHistory();
    Helper::saveBorrowingUsers();
    Helper::saveReservationUsers();
    Helper::saveUsers();
    Helper::saveLibraryEvents();
    Helper::saveLibraryResources();
    Helper::saveOpeningSchedule();
    Helper::saveEmails();
}

void Helper::load(){
    Helper::loadLibraryResources();
    Helper::loadBorrowingHistory();
    Helper::loadBorrowingUsers();
    Helper::loadReservationUsers();
    Helper::loadUsers();
    Helper::loadLibraryEvents();
    Helper::loadOpeningSchedule();
    Helper::loadEmails();
}


bool Helper::sendEmail(QString recipient, QString subject, QString body)

{
    MimeMessage message;
    EmailAddress sender("librarymanagementsystem.norep@gmail.com", "LibraryManagementSystem");
    message.setSender(sender);
    EmailAddress to(recipient, QString());
    message.addRecipient(to);
    message.setSubject(subject);

    MimeText textPart;
    textPart.setText(body);
    message.addPart(&textPart);

    SmtpClient smtp("smtp.gmail.com",
                    465,
                    SmtpClient::SslConnection);

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "SMTP: failed to connect";
        return false;
    }

    smtp.login("librarymanagementsystem.norep@gmail.com", "gbxnhrqsmyscgvlk");
    if (!smtp.waitForAuthenticated()) {
        qDebug() << "SMTP: authentication failed";
        return false;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        qDebug() << "SMTP: sendMail failed";
        return false;
    }

    smtp.quit();
    return true;
}



void Helper :: sendEmailToAll(QString subject,QString body){
    for(Email email : Library::mainLibrary().libraryEmails){
        sendEmail(QString::fromStdString(email.getEmail()), subject, body);
    }
}
