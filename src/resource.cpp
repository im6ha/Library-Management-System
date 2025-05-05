#include "resource.h"


Resource :: Resource(string inputTitle, string author, int publicationYear, int quantity,string type){

    setAll(inputTitle,author,publicationYear,quantity,type);

}



Resource :: Resource (){
    reservations=0;
    isBorrowed= false;
}

bool Resource :: setAll(string title, string author, int publicationYear, int quantity,string type){
    setType(type);
    setTitle (title);
    setAuthor(author);
    setPublicationYear(publicationYear);
    setQuantity(quantity);
    setReservations(0);
    isBorrowed= false;

    return setTitle (title) && setAuthor(author) && setPublicationYear(publicationYear)&& setQuantity(quantity);
}


bool Resource :: operator==(Resource r){
    if(title == r.title && author == r.author && publicationYear == r.publicationYear && type == r.type)
        return true;

    return false;
}

string Resource :: getAuthor(){
    return author;
}


string Resource :: getTitle(){
    return title;
}

int Resource :: getPublicationYear(){
    return publicationYear;
}

int Resource :: getQuantity(){
    return quantity;
}

string Resource::getType(){
    return type;
}

bool Resource :: getAvailability(){
    return availability;
}

int Resource :: getReservations(){
    return reservations;
}

bool Resource::setTitle(string inputTitle) {
    if (inputTitle.size() > 100) return false;
    title = inputTitle;
    return true;
}


bool Resource::setAuthor(string inputAuthor) {
    bool check = true;
    for (int i = 0; i < inputAuthor.size(); i++) {
        if (!isalpha(inputAuthor[i]) && inputAuthor[i] != '.' && inputAuthor[i] != ' ') {
            check = false;
            break;
        }
    }

    if (check) {
        author = "";
        vector<string> words;
        int start, end;
        start =0;
        while ((end = inputAuthor.find(' ', start)) != string::npos) {
            if (end > start) {
                words.push_back(inputAuthor.substr(start, end - start));
            }
            start = end + 1;
        }
        if (start < inputAuthor.length()) {
            words.push_back(inputAuthor.substr(start));
        }        if (words.empty()) return false;

        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                words[i][j] = tolower(words[i][j]);
            }
            if (!words[i].empty() && isalpha(words[i][0])) words[i][0] = toupper(words[i][0]);
        }

        author = words[0];
        for (int i = 1; i < words.size(); i++) {
            author += " " + words[i];
        }

        return true;
    }

    return false;
}



bool Resource :: setQuantity(int inputQuantity){
    if (inputQuantity >= 0){
        quantity = inputQuantity;
        if (inputQuantity > 0) availability = true;
        else availability = false;
        return true;
    }

    return false;
}
bool Resource::setPublicationYear(int year) {

    std::time_t t = std::time(nullptr);

    std::tm* localTime = std::localtime(&t);

    int current_year  = 1900 + localTime->tm_year;


    if (year <= current_year && year >= 0) {
        publicationYear = year;
        return true;
    }
    return false;
}

void Resource :: setType(string inputType){
    transform(inputType.begin(), inputType.end(), inputType.begin(), ::tolower); // convert input type to lower_case
    if (inputType == "book" || inputType == "article"|| inputType == "digital content"){
        if (inputType == "book") {
            type = "Book";
             return;
        }

        if (inputType == "article") {
            type ="Article";
            return;
        }

        if (inputType == "digital content"){
            type = "Digital Content";
            return;
        }
    }
    else type = "Other";
}

void Resource :: setAvailability(bool avail){
    availability = avail;
}

void Resource :: setReservations(int reservation){
    reservations = reservation;
}


Resource Resource :: operator+=(int a){
    quantity += a;
    return *(this);
}

Resource Resource :: operator--(){
    if (quantity> 0) quantity--;
    return (*this);
}


bool Resource :: operator!=(Resource r){
    if (!(*(this) == r)) return true;
    return false;
}


BorrowedResource::BorrowedResource(Resource r, Date duedate, bool physical):Resource(r){
    dueDate = duedate;
    isPhysical = physical;
}



