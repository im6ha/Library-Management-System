#include "windows/borrowwindow.h"
#include "library.h"
#include "qmessagebox.h"
#include "ui_borrowwindow.h"
#include "windows/librarymanagementsystem.h"
#include "windows/reservewindow.h"

borrowWindow::borrowWindow(User* user, LibraryManagementSystem* mainwindow, QWidget *parent)
    : QDialog(parent), ui(new Ui::borrowWindow), currentUser(user),mainwindow(mainwindow)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System");
    QLabel *background = new QLabel(this);
    QPixmap pixmap(":/media/media/background.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();
    ui->byId->setChecked(true);
    ui->isPhysical->setChecked(true);
    ui->userInfo->setEnabled(true);
    ui->currentDate->setChecked(true);
    if (!currentUser->getAdmin()){
        ui->useLoggedin->setChecked(true);
        ui->isUsername->setChecked(true);
    }
    history=nullptr;
    if(currentUser->getAdmin()){
        ui->password->setEnabled(false);
    }

}

borrowWindow::~borrowWindow()
{
    delete ui;
}



void borrowWindow::on_useLoggedin_stateChanged(int state)
{
    if (state == Qt::Checked){
        if(currentUser->getAdmin()){
            ui->useLoggedin->setChecked(false);
            QMessageBox :: warning(this,"","Can't Borrow/Renew Borrow Items as Admin User");
            return;
        }
        ui->userInfo->setEnabled(false);
    }

    if (state == Qt::Unchecked){
        ui->userInfo->setEnabled(true);
    }
}




void borrowWindow::on_isId_clicked()
{
    ui->id->setEnabled(true);
    ui->username->clear();
    ui->username->setEnabled(false);
}


void borrowWindow::on_isUsername_clicked()
{
    ui->username->setEnabled(true);
    ui->id->clear();
    ui->id->setEnabled(false);
}


void borrowWindow::on_byResource_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->byId->setChecked(false);
        ui->inputAuthor->setEnabled(true);
        ui->inputPublicationYear->setEnabled(true);
        ui->inputTitle->setEnabled(true);
    }
    else{
        ui->byId->setChecked(true);
        ui->inputAuthor->setEnabled(false);
        ui->inputPublicationYear->setEnabled(false);
        ui->inputTitle->setEnabled(false);
    }
}


void borrowWindow::on_byId_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->byResource->setChecked(false);
        ui->ID->setEnabled(true);
        ui->book->setChecked(true);
        ui->type_2->setEnabled(false);
    }

    else{
        ui->byResource->setChecked(true);
        ui->type_2->setEnabled(true);
        ui->ID->setEnabled(false);
    }
}


void borrowWindow::on_borrow_clicked()
{
    User* uPtr = nullptr;
    if (ui->useLoggedin->isChecked()){
        uPtr = currentUser;
    }
    else {
        int findUser;
        if (ui->isId->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->id->value());
        }
        else{
            findUser = Library::mainLibrary().findUser(ui->username->text().toStdString());
        }
        if (findUser == -1){
            QMessageBox::warning(this, "", "Given ID doesn't match an existing user");
            return;
        }
        if (Library::mainLibrary().libraryUsers[findUser].getPassword() == ui->password->text().toStdString() || currentUser->getAdmin()){
            uPtr = &Library::mainLibrary().libraryUsers[findUser];
        }
        else {
            QMessageBox::warning(this, "", "Password Incorrect");
            return;
        }
    }
    if (!uPtr) return;

    string type;
    if (ui->book->isChecked() || ui->book_2->isChecked()){
        type = "book";
    }
    else if (ui->article->isChecked() || ui->article_2->isChecked()){
        type = "article";
    }
    else if (ui->digitalcontent->isChecked() || ui->digitalcontent_2->isChecked()){
        type = "digital content";
    }
    else if (ui->other->isChecked() || ui->other_2->isChecked()){
        type = "other";
    }

    // Validate date
    QDate date = ui->date->date();
    if(date < QDate::currentDate()){
        QMessageBox::warning(this, "", "The Enterred Date Must be Equal or Greater than Current Date");
        return;
    }
    Date d(date.day(), date.month(), date.year());

    // Find resource ID
    pair<int,int> id;
    if(ui->byId->isChecked()){
        id = make_pair(Helper:: setRowIndex(type), ui->id2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r == Resource("out of range", "out of range", 0)){
            QMessageBox::warning(this, "", "No Resource Found With The Given ID");
            return;
        }
    }
    if (ui->byResource->isChecked()){
        id = Library::mainLibrary().findResource(Resource(ui->inputTitle->text().toStdString(),
                                                          ui->inputAuthor->text().toStdString(),
                                                          ui->inputPublicationYear->value(),
                                                          0, type));
        if (id == make_pair(-1,-1)){
            QMessageBox::warning(this, "", "No Resource Found With The Given Information");
            return;
        }
    }

    // Now pass the actual User instance to the borrowResource function.
    int state = Library::mainLibrary().borrowResource(*uPtr,
                                                      Library::mainLibrary().libraryResources[id.first][id.second],
                                                      d, ui->isPhysical->isChecked());

    if (state == 0){
        QMessageBox::information(this, "Success", "Resource Borrowed Successfully");
        return;
    }
    if (state == -2){
        QMessageBox::warning(this, "", "User Can't Borrow Same Resource Twice Before Returning the First One");
        return;
    }
    if (state == -3){
        QMessageBox::warning(this, "", "Not Enough Quantity (Considering Number of Reservations as well)");
        int reply = QMessageBox::question(nullptr, "Not Enough Qunatity",
                                          "Not Enough Quantity\nWould You Like To Reserve the Resource",
                                          QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            this->hide();
            reservewindow->show();
        }
        return;
    }
}





void borrowWindow::on_renew_clicked()
{
    User* uPtr = nullptr;
    if (ui->useLoggedin->isChecked()){
        uPtr = currentUser;
    }
    else{
        int findUser;
        if (ui->isId->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->id->value());
        }
        else{
            findUser = Library::mainLibrary().findUser(ui->username->text().toStdString());
        }
        if (findUser == -1){
            QMessageBox::warning(this, "", "Given ID doesn't match an existing user");
            return;
        }
        if (Library::mainLibrary().libraryUsers[findUser].getPassword() == ui->password->text().toStdString()){
            uPtr = &Library::mainLibrary().libraryUsers[findUser];
        }
        else {
            QMessageBox::warning(this, "", "Password Incorrect");
            return;
        }
    }
    if (!uPtr) return;

    string type;
    if ((ui->byId->isChecked() && ui->book->isChecked()) || (ui->byResource->isChecked() && ui->book_2->isChecked())){
        type = "book";
    }
    else if ((ui->byId->isChecked() && ui->article->isChecked()) || (ui->byResource->isChecked() && ui->article_2->isChecked())){
        type = "article";
    }
    else if ((ui->byId->isChecked() && ui->digitalcontent->isChecked()) || (ui->byResource->isChecked() && ui->digitalcontent_2->isChecked())){
        type = "digital content";
    }
    else if ((ui->byId->isChecked() && ui->other->isChecked()) || (ui->byResource->isChecked() && ui->other_2->isChecked())){
        type = "other";
    }

    QDate date = ui->date->date();
    if(date < QDate::currentDate()){
        QMessageBox::warning(this, "", "The Enterred Date Must be Equal or Greater than Current Date");
        return;
    }
    Date d(date.day(), date.month(), date.year());

    if(ui->byId->isChecked()){
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->id2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r == Resource("out of range", "out of range", 0)){
            QMessageBox::warning(this, "", "No Resource Found With The Given ID");
            return;
        }
        if(Library::mainLibrary().renewBorrow(*uPtr, Library::mainLibrary().libraryResources[id.first][id.second], d)){
            QMessageBox::information(this, "Success", "Borrowed Renewed Successfully");
            return;
        }
        QMessageBox::warning(this, "", "This Resource isn't Borrowed by The Given User");
    }
    if (ui->byResource->isChecked()){
        pair<int,int> id = Library::mainLibrary().findResource(Resource(ui->inputTitle->text().toStdString(),
                                                                         ui->inputAuthor->text().toStdString(),
                                                                         ui->inputPublicationYear->value(),
                                                                         0, type));
        if (id == make_pair(-1,-1)){
            QMessageBox::warning(this, "", "No Resource Found With The Given Information");
            return;
        }
        if(Library::mainLibrary().renewBorrow(*uPtr, Library::mainLibrary().libraryResources[id.first][id.second], d)){
            QMessageBox::information(this, "Success", "Borrowed Renewed Successfully");
            return;
        }
        QMessageBox::warning(this, "", "This Resource isn't Borrowed by The Given User");
    }
}


void borrowWindow::on_return_2_clicked()
{
    User* uPtr = nullptr;
    if (ui->useLoggedin->isChecked()){
        uPtr = currentUser;
    }
    else{
        int findUser;
        if (ui->isId->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->id->value());
        }
        else{
            findUser = Library::mainLibrary().findUser(ui->username->text().toStdString());
        }
        if (findUser == -1){
            QMessageBox::warning(this, "", "Given ID doesn't match an existing user");
            return;
        }
        if (Library::mainLibrary().libraryUsers[findUser].getPassword() == ui->password->text().toStdString() || currentUser->getAdmin() ){
            uPtr = &Library::mainLibrary().libraryUsers[findUser];
        }
        else {
            QMessageBox::warning(this, "", "Password Incorrect");
            return;
        }
    }
    if (!uPtr) return;

    string type;
    if ((ui->byId->isChecked() && ui->book->isChecked()) || (ui->byResource->isChecked() && ui->book_2->isChecked())){
        type = "book";
    }
    else if ((ui->byId->isChecked() && ui->article->isChecked()) || (ui->byResource->isChecked() && ui->article_2->isChecked())){
        type = "article";
    }
    else if ((ui->byId->isChecked() && ui->digitalcontent->isChecked()) || (ui->byResource->isChecked() && ui->digitalcontent_2->isChecked())){
        type = "digital content";
    }
    else if ((ui->byId->isChecked() && ui->other->isChecked()) || (ui->byResource->isChecked() && ui->other_2->isChecked())){
        type = "other";
    }

    QDate date = ui->date->date();
    if(date < QDate::currentDate()){
        QMessageBox::warning(this, "", "The Enterred Date Must be Equal or Greater than Current Date");
        return;
    }
    Date d(date.day(), date.month(), date.year());

    if(ui->byId->isChecked()){
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->id2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r == Resource("out of range", "out of range", 0)){
            QMessageBox::warning(this, "", "No Resource Found With The Given ID");
            return;
        }
        if(Library::mainLibrary().returnResource(*uPtr, Library::mainLibrary().libraryResources[id.first][id.second], d)){
            QMessageBox::information(this, "Success", "Resource Returned Successfully");
            return;
        }
        QMessageBox::warning(this, "", "This Resource isn't Borrowed by The Given User");
    }
    if (ui->byResource->isChecked()){
        pair<int,int> id = Library::mainLibrary().findResource(Resource(ui->inputTitle->text().toStdString(),
                                                                         ui->inputAuthor->text().toStdString(),
                                                                         ui->inputPublicationYear->value(),
                                                                         0, type));
        if (id == make_pair(-1,-1)){
            QMessageBox::warning(this, "", "No Resource Found With The Given Information");
            return;
        }
        if(Library::mainLibrary().returnResource(*uPtr, Library::mainLibrary().libraryResources[id.first][id.second], d)){
            QMessageBox::information(this, "Success", "Resource Returned Successfully");
            return;
        }
        QMessageBox::warning(this, "", "This Resource isn't Borrowed by The Given User");
    }
}

void borrowWindow::on_currentDate_stateChanged(int state)
{
    if (state==Qt::Checked){
        ui->date->setEnabled(false);
        ui->date->setDate(QDate::currentDate().addDays(7)); // by default currentdate + week
    }
    else {
        ui->date->setEnabled(true);
    }
}


void borrowWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void borrowWindow::on_hisotry_clicked()
{

    history = new borrowingHistoryWindow(this);
    history->setAttribute(Qt::WA_DeleteOnClose);
    history->show();
}

