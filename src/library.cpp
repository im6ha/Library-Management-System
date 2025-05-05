#include "library.h"
#include <QDate>

Library& Library::mainLibrary() {
    static Library l;
    return l;
}


pair <int,int> Library::addResource(Resource r){
    pair<int,int> index = findResource(r);
    if (index != make_pair(-1,-1)){
        libraryResources[index.first][index.second]+=r.getQuantity();
    }
    else{
        int j = Helper :: setRowIndex(r.getType());
        r.id.first =j;
        r.id.second= libraryResources[j].size();
        libraryResources[j].push_back(r);
    }
    return index;
}

int Library::removeResource(pair<int,int> id) {
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return -1;
    if (!libraryResources[id.first][id.second].isBorrowed){
        libraryResources[id.first].erase(libraryResources[id.first].begin() + id.second);
        for (int i = id.second; i < libraryResources[id.first].size(); i++){
            libraryResources[id.first][i].id.second = i;
        }
        return 0;
    }
    return -2;

}

bool Library :: editTitle(pair<int,int> id, string newTitle){
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return false;
    libraryResources[id.first][id.second].setTitle(newTitle);
    return true;
}

bool Library :: editAuthor(pair<int,int> id, string newAuthor){
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return false;
    libraryResources[id.first][id.second].setAuthor(newAuthor);
    return true;
}
bool Library :: editPublicationYear(pair<int,int> id, int newPublicationYear){
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return false;
    libraryResources[id.first][id.second].setPublicationYear(newPublicationYear);
    return true;
}

bool Library :: editQuantity(pair<int,int> id, int newQuantity){
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return false;
    libraryResources[id.first][id.second].setQuantity(newQuantity);
    return true;
}

bool Library :: editType(pair<int,int> id, string newType){
    if (id.first>= 4 || id.second>=libraryResources[id.first].size()) return false;

    Resource copy = libraryResources[id.first][id.second];

    copy.setType(newType);
    int newRow = Helper :: setRowIndex(newType);
    copy.id = make_pair(newRow,libraryResources[newRow].size());
    libraryResources[newRow].push_back(copy);
    removeResource(id);
    if (copy.isBorrowed){
        for (int i=0; i < Library::mainLibrary().libraryUsers.size(); i++){
            int index = findBorrowedResource(Library::mainLibrary().libraryUsers[i], copy);
            if(index !=-1){
                Library::mainLibrary().libraryUsers[i].borrowedResources[index].id = make_pair (newRow,libraryResources[newRow].size()-1);
            }
        }

        return true;
    }
    return true;
}

bool Library :: editResource(pair<int,int> id, Resource newResource, bool changeTitle,bool changeAuthor, bool changeQuantity, bool changePublicationYear, bool changeType){
    bool result = true;
    if (changeTitle)
        result = result && editTitle(id, newResource.getTitle());
    if (changeAuthor)
        result = result && editAuthor(id, newResource.getAuthor());
    if (changePublicationYear)
        result = result && editPublicationYear(id, newResource.getPublicationYear());
    if (changeQuantity)
        result = result && editQuantity(id, newResource.getQuantity());
    if (changeType)
        result = result && editType(id, newResource.getType());

    return result;

}



void Library :: setOneDLibraryResources(){
    oneD_libraryResources.clear();
    for (int i = 0; i < 4; i++) {
        if(libraryResources[i].empty()) continue;
        for (int j=0; j<libraryResources[i].size(); j++) {
            oneD_libraryResources.push_back(libraryResources[i][j]);
        }

    }
}

const vector<QString> Library::errors = {
    "Title Can't Exceed 100 Characters",
    "Author Name Must Contain Only Alphabetic Characters (or dots)",
    "Publication Year Cannot Exceed Current Year"
};

//Borrowing System functions


int Library :: borrowResource(User& person, pair<int,int> id, Date dueDate, bool isphysical){
    if (findResource(id) == Resource("out of range", "out of range", 0)) return -1;
    Resource &r = libraryResources[id.first][id.second];
    for (int i=0; i<person.borrowedResources.size(); i++){
        if (libraryResources[person.borrowedResources[i].id.first][person.borrowedResources[i].id.second] == r){
            return -2; //don't allow same user to borrow same resource before returning same one
        }
    }
    if(r.getReservations() >= r.getQuantity()) return -3;

    --r;
    person.borrowedResources.push_back(BorrowedResource(findResource(id), dueDate,isphysical));
    borrowingUsers.push_back(person);
    r.isBorrowed= true;
    if (r.getQuantity()==0) r.setAvailability(false);
    return 0;
}


int Library :: borrowResource(User& person,Resource& r, Date dueDate, bool isphysical){
    return borrowResource(person, findResource(r), dueDate, isphysical);
}


bool Library :: returnResource(User& person, Resource& r, Date returnDate){
    int index = findBorrowedResource(person,r);
    if (index == -1) return false;
    bool onTime= (person.borrowedResources[index].dueDate >= returnDate)? true: false;
    History historyInstance (person,r,returnDate, onTime);
    borrowingHistory.push_back(historyInstance);

    person.borrowedResources.erase(person.borrowedResources.begin() + index);

    Library::mainLibrary().borrowingUsers.erase(Library::mainLibrary().borrowingUsers.begin()+index);
    libraryResources[r.id.first][r.id.second]+=1;
    bool isBorrowed= false;


    //check if it's borrowed by another user
    bool exitloops=false;
    for (int i =0; i<borrowingUsers.size(); i++){
        for (int j=0; j<borrowingUsers[i].borrowedResources.size(); j++){
            if(libraryResources[borrowingUsers[i].borrowedResources[j].id.first]
                                [borrowingUsers[i].borrowedResources[j].id.second] == r){
                isBorrowed = true;
                exitloops=true;
                break;
            }
        }
        if (exitloops) break;
    }
    libraryResources[r.id.first][r.id.second].isBorrowed = isBorrowed;
    return true;
}

void Library :: reserveResource(User& person, Resource& r){ //if don't have resource it gets added
    pair<int,int> id = findResource(r);
    if (id != make_pair(-1,-1)){
        person.indexOfReservedResources.push_back(id);
        libraryResources[id.first][id.second].setReservations(libraryResources[id.first][id.second].getReservations()+1);
        reservationUsers.push_back(person);
        return;
    }
    r.setQuantity(0);
    addResource(r);
    reserveResource(person,r);
}

bool Library :: renewBorrow (User& person,Resource r,Date dueDate){
    int index = findBorrowedResource(person,r);
    if (index != -1 && dueDate >= person.borrowedResources[index].dueDate){
        person.borrowedResources[index].dueDate = dueDate;
        return true;
    }
    return false;
}
int Library::findReservation(User& person, Resource& r) {
    for (int i = 0; i < person.indexOfReservedResources.size(); i++) {

        if (libraryResources[person.indexOfReservedResources[i].first][person.indexOfReservedResources[i].second] == r) {
            return i;
        }
    }
    return -1;
}




bool Library::deleteReservation(User& person, Resource& r) {
    int index = findReservation(person, r);
    if (index == -1) return false;

    int row = person.indexOfReservedResources[index].first;
    int col = person.indexOfReservedResources[index].second;
    libraryResources[row][col].setReservations(libraryResources[row][col].getReservations() -1);

    person.indexOfReservedResources.erase(person.indexOfReservedResources.begin() + index);

    if (person.indexOfReservedResources.empty()) {
        for (int i = 0; i < reservationUsers.size(); i++) {
            if (reservationUsers[i].getUsername() == person.getUsername()) {
                reservationUsers.erase(reservationUsers.begin() + i);
                break;
            }
        }
    }
    return true;
}

//Sorting, Finding functions



vector<pair<int,int>> Library :: findResourceTitle(string title){
    vector<pair<int,int>> result;
    for(int i =0; i < 4; i++){
        if (libraryResources[i].empty()) continue;
        for (int j=0; j< libraryResources[i].size(); j++){
            string lowerText = libraryResources[i][j].getTitle(); //case-insensetive
            transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
            if (lowerText==title) result.push_back(make_pair(i,j));
        }
    }
    if (result.empty()) result.push_back(make_pair(-1, -1));
    return result;
}

vector<pair<int,int>> Library :: findResourceAuthor(string author){
    vector<pair<int,int>> result;
    for (int i =0; i< 4; i++){
        if (libraryResources[i].empty()) continue;
        for (int j=0; j<libraryResources[i].size(); j++){
            string lowerText = libraryResources[i][j].getAuthor(); //case-insensetive
            transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
            if (lowerText == author) result.push_back(make_pair(i,j));
        }
    }
    if (result.empty()) result.push_back(make_pair(-1,-1));
    return result;
}

vector <pair<int,int>> Library :: findResourcePublication(int publicationYear){
    vector<pair<int,int>> result;
    for (int i =0; i< 4; i++){
        if (libraryResources[i].empty()) continue;
        for (int j=0; j<libraryResources[i].size(); j++){
            if (libraryResources[i][j].getPublicationYear() == publicationYear) result.push_back(make_pair(i,j));
        }
    }
    if (result.empty()) result.push_back(make_pair(-1,-1));
    return result;
}


pair<int,int> Library :: findResource(Resource r){
    int i = Helper :: setRowIndex(r.getType());
    if (i < 4 && !libraryResources[i].empty()) {
        for (int j = 0; j < libraryResources[i].size(); j++){
            if (libraryResources[i][j] == r)
                return make_pair(i, j);
        }
    }
    return make_pair(-1,-1);
}

Resource Library :: findResource(pair<int,int> id){
    Resource outOfRange("out of range", "out of range", 0);
    if (id.first >= 0 && id.first < 4 && id.second >= 0 && id.second < libraryResources[id.first].size()){
        return libraryResources[id.first][id.second];
    }
    return outOfRange;
}

vector<pair<int,int>> Library :: findResourceType(string type){
    vector<pair<int,int>> result;
    int row = Helper :: setRowIndex(type);
    if (row < 4 && row >= 0 && !libraryResources[row].empty()) {
        for (int i =0; i < libraryResources[row].size(); i++){
            result.push_back(make_pair(row,i));
        }
    }
    if(result.empty()) result.push_back(make_pair(-1,-1));
    return result;
}

int Library :: findBorrowedResource(User person, Resource r){
    for (int i =0; i < person.borrowedResources.size(); i++){
        if (libraryResources[person.borrowedResources[i].id.first]
                            [person.borrowedResources[i].id.second] == r){
            return i;
        }
    }
    return -1;
}

void Library :: sortTitle(){
    setOneDLibraryResources();
    sort(oneD_libraryResources.begin(), oneD_libraryResources.end(),
         [](Resource a, Resource b){return a.getTitle()<b.getTitle();});
}

void Library :: sortPublicationYear(){
    setOneDLibraryResources();
    sort(oneD_libraryResources.begin(), oneD_libraryResources.end(),
         [](Resource a, Resource b){return a.getPublicationYear()>b.getPublicationYear();});
}

void Library :: sortQuantity(){
    setOneDLibraryResources();
    sort(oneD_libraryResources.begin(), oneD_libraryResources.end(),
         [](Resource a, Resource b){return a.getQuantity()>b.getQuantity();});
}

void Library :: sortNumberOfReservations(){
    setOneDLibraryResources();
    sort(oneD_libraryResources.begin(), oneD_libraryResources.end(),
         [](Resource a, Resource b){return a.getReservations()<b.getReservations();});
}

void Library :: sortAuthor(){
    setOneDLibraryResources();
    sort(oneD_libraryResources.begin(), oneD_libraryResources.end(),
         [](Resource a, Resource b){return a.getAuthor()<b.getAuthor();});
}


vector<Resource> Library::availabileResources(){
    vector<Resource> available;
    for (int i=0; i < 4; i++){
        for(Resource r: libraryResources[i]){
            if (r.getAvailability()) available.push_back(r);
        }
    }
    return available;
}



vector<pair<int,int>> Library::findResourceKeyword(string keyword){
    vector<pair<int,int>> matches;
    for (int i = 0; i < 4; i++){
        if (libraryResources[i].empty()) continue;
        for (int j = 0; j < libraryResources[i].size(); j++){
            string lowerText = libraryResources[i][j].getTitle();
            transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
            if (lowerText.find(keyword) != string::npos){
                matches.push_back(make_pair(i,j));
            }
        }
    }
    if (matches.empty()) matches.push_back(make_pair(-1, -1));
    return matches;
}


vector<pair<int,int>> Library::findResourceKeywordAuthor(string keyword){
    vector<pair<int,int>> matches;
    for (int i = 0; i < 4; i++){
        if (libraryResources[i].empty()) continue;
        for (int j = 0; j < libraryResources[i].size(); j++){
            string lowerText = libraryResources[i][j].getAuthor();
            transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
            if (lowerText.find(keyword) != string::npos){
                matches.push_back(make_pair(i,j));
            }
        }
    }
    if (matches.empty()) matches.push_back(make_pair(-1, -1));
    return matches;
}


void Library:: setOpeningTimes(bool isOpenSunday, Time sundayOpening, Time sundayClosing,
                              bool isOpenMonday, Time mondayOpening, Time mondayClosing,
                              bool isOpenTuesday, Time tuesdayOpening, Time tuesdayClosing,
                              bool isOpenWednesday, Time wednesdayOpening, Time wednesdayClosing,
                              bool isOpenThursday, Time thursdayOpening, Time thursdayClosing,
                              bool isOpenFriday, Time fridayOpening, Time fridayClosing,
                              bool isOpenSaturday, Time saturdayOpening, Time saturdayClosing)
{
    if (isOpenSunday) {
        openingTimes[0] = sundayOpening;
        closingTimes[0] = sundayClosing;
    }
    if (isOpenMonday) {
        openingTimes[1] = mondayOpening;
        closingTimes[1] = mondayClosing;
    }
    if (isOpenTuesday) {
        openingTimes[2] = tuesdayOpening;
        closingTimes[2] = tuesdayClosing;
    }
    if (isOpenWednesday) {
        openingTimes[3] = wednesdayOpening;
        closingTimes[3] = wednesdayClosing;
    }
    if (isOpenThursday) {
        openingTimes[4] = thursdayOpening;
        closingTimes[4] = thursdayClosing;
    }
    if (isOpenFriday) {
        openingTimes[5] = fridayOpening;
        closingTimes[5] = fridayClosing;
    }
    if (isOpenSaturday) {
        openingTimes[6] = saturdayOpening;
        closingTimes[6] = saturdayClosing;
    }

    isOpen[0]= isOpenSunday;
    isOpen[1]= isOpenMonday;
    isOpen[2]= isOpenTuesday;
    isOpen[3]= isOpenWednesday;
    isOpen[4]= isOpenThursday;
    isOpen[5]= isOpenFriday;
    isOpen[6]= isOpenSaturday;


}

void Library::refreshEvents(){
    for (int i = 0; i < libraryEvents.size(); i++){
        if (libraryEvents[i].endingDate <= QDate::currentDate() && libraryEvents[i].endingTime <= QTime::currentTime()){
            libraryEvents.erase(libraryEvents.begin()+i);
            i--;
        }
    }
}


int Library:: setEvent(string title,string description,Date openingD,Time openingT,Date closingD,Time closingT){
    refreshEvents();

    if (openingD > closingD || (openingD == closingD && openingT >= closingT))
        return -2;

    for (int i=0;i<libraryEvents.size(); i++){
        if (title == libraryEvents[i].title)
            return -1;
    }

    Event newEvent(title,description,openingD,closingD,openingT,closingT);
    libraryEvents.push_back(newEvent);

    return 0;
}

bool Library::deleteEvent(string title){
    for (int i = 0; i < libraryEvents.size(); i++){
        if (libraryEvents[i].title == title) {
            libraryEvents.erase(libraryEvents.begin()+i);
            return true;
        }
    }
    return false;
}

bool Library :: addEmail(Email e){
    if(!Email :: checkEmail(e.getEmail())) return false;
    libraryEmails.push_back(e);
    return true;
}

bool Library :: deleteEmail(Email e){
    for(int i=0; i < libraryEmails.size(); i++){
        if (e.getEmail() == libraryEmails[i].getEmail()){
            libraryEmails.erase(libraryEmails.begin()+i);
            return true;
        }
    }
    return false;
}

void Library :: addUser(User u){
    Library::mainLibrary().libraryUsers.push_back(u);
}

bool Library :: deleteUser(int id){
    int index=-1;
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getId()== id){
            index =i;
            break;
        }
    }
    if (index == -1) return false;
    Library::mainLibrary().libraryUsers.erase(Library::mainLibrary().libraryUsers.begin() + index);
    return true;
}

bool Library :: deleteUser(string user){
    int index=-1;
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getUsername() == user){
            index =i;
            break;
        }
    }
    if (index == -1) return false;
    Library::mainLibrary().libraryUsers.erase(Library::mainLibrary().libraryUsers.begin() + index);
    return true;
}


pair<int,int> Library :: login (string user, string pass){
    bool usernameFound = false;
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getUsername()==user) {
            usernameFound = true;
            if (Library::mainLibrary().libraryUsers[i].getPassword() == pass &&
                !Library::mainLibrary().libraryUsers[i].getAdmin()) return make_pair(0,i);
            if (Library::mainLibrary().libraryUsers[i].getPassword() == pass &&
                Library::mainLibrary().libraryUsers[i].getAdmin()) return make_pair(1,i);
        }
    }
    if (usernameFound) return make_pair(-1,-1);
    return make_pair(-2,-2);
}

pair<int,int> Library :: login (int id, string pass){
    bool idFound = false;
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getId()==id) {
            idFound = true;
            if (Library::mainLibrary().libraryUsers[i].getPassword() == pass &&
                !Library::mainLibrary().libraryUsers[i].getAdmin()) return make_pair(0,i);
            if (Library::mainLibrary().libraryUsers[i].getPassword() == pass &&
                Library::mainLibrary().libraryUsers[i].getAdmin()) return make_pair(1,i);
        }
    }
    if (idFound) return make_pair(-1,-1);
    return make_pair(-2,-2);
}


int Library:: findUser(int id){
    for (int i =0; i<Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getId()==id) return i;
    }
    return -1;
}
int Library :: findUser(string username){
    for (int i =0; i<Library::mainLibrary().libraryUsers.size(); i++){
        if (Library::mainLibrary().libraryUsers[i].getUsername()==username) return i;
    }
    return -1;
}

