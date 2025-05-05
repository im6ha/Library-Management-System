#include "windows/loginwindow.h"
#include "qmessagebox.h"
#include "ui_loginwindow.h"
#include <cctype>
#include "windows/librarymanagementsystem.h"


loginWindow::loginWindow(LibraryManagementSystem* main, QWidget *parent)
    : QDialog(parent), ui(new Ui::loginWindow), mainwindow(main)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System");

    ui->id->setRange(0,Library::mainLibrary().libraryUsers.size());
    ui->isUsername->setChecked(true);
    ui->id->setEnabled(false);


    QLabel *background = new QLabel(this);
    QPixmap pixmap("../../media/loginWindow.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();

    Helper::load();


}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_isUsername_clicked()
{
    ui->id->setEnabled(false);
    ui->username->setEnabled(true);
}

void loginWindow::on_isId_clicked()
{
    ui->username->setEnabled(false);
    ui->id->setEnabled(true);
}


void loginWindow::on_signup_clicked()
{

    if (ui->isId->isChecked() || ui->username->text().isEmpty()){
        QMessageBox :: warning(this,"", "The Username Filed Must Not be Empty");
        return;
    }
    string username =ui->username->text().toStdString();
    string password= ui->password->text().toStdString();
    User test;
    User :: currentId--;
    int errorCheck = test.setUsername(username);

    switch (errorCheck){
    case -1:
        QMessageBox :: warning(this,"", "Username Can't Start With a Number");
        return;
    case -2:
        QMessageBox :: warning(this,"", "Username Must Only Contain Alphabetic or"
                                 "Numeric Characters");
        return;
    case -3:
        QMessageBox :: warning(this,"", "Username Can't Exceed 10 Characters");
        return;
    case -4:
        QMessageBox :: warning(this,"", "Username Already Taken");
        return;
    case -5:
        QMessageBox :: warning(this,"", "Username Can't Have Uppercase Letters");
        return;
    }

    errorCheck = test.setPassword(password);
    switch (errorCheck){
    case -1:
        QMessageBox :: warning(this,"", "Password Can't be Less Than 4 Characters");
        return;
    case -2:
        QMessageBox :: warning(this,"", "Password Can't Exceed 12 Characters");
        return;
    case -3:
        QMessageBox :: warning(this,"", "Password Must Contain a Number");
        return;
    case -4:
        QMessageBox :: warning(this,"", "Password Must Contain an Alphabetic Character");
        return;
    case -5:
        QMessageBox :: warning(this,"", "Password Contains Unallowed Special Characters");
        return;
    }

    Library::mainLibrary().addUser(User(username,password,false));
    QMessageBox::information(this, "Success", "User Added Successfully\nUsername: " +
                QString::fromStdString(Library::mainLibrary().libraryUsers.back().getUsername()) +
                "\nID: " + QString::number(Library::mainLibrary().libraryUsers.back().getId()));

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Success",
                                  "User Added Successfully\nUsername: " +
                                      QString::fromStdString(Library::mainLibrary().libraryUsers.back().getUsername()) +
                                      "\nID: " + QString::number(Library::mainLibrary().libraryUsers.back().getId()) +
                                      "\nWould You like To Log In Using This User?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        mainwindow->setUser(&Library::mainLibrary().libraryUsers.back());
        this ->hide();
        mainwindow->show();

    } else {
        return;
    }
}


void loginWindow::on_login_clicked()
{
    if (ui->isUsername->isChecked() && ui->username->text().isEmpty()){
        QMessageBox:: warning(this,"","Identifier Field Must Not be Empty");
        return;
    }
    if (ui->password->text().isEmpty()){
        QMessageBox:: warning(this,"","Password Field Must Not be Empty");
        return;
    }

    pair<int,int> loginType;
    string password = ui->password->text().toStdString();
    if (ui->isId->isChecked()){
        int identifier = ui->id->value();
        loginType = Library::mainLibrary().login(identifier, password);
    }

    else {
        string identifier = ui->username->text().toStdString();
        loginType = Library::mainLibrary().login(identifier, password);
    }

    switch(loginType.first){
    case -1:
        QMessageBox:: warning(this, "Wrong Pasword", "The Enterred Password Doesn't Match The Username");
        return;
    case -2:
        QMessageBox:: warning(this, "Wrong Username", "The Enterred Username/ID Doesn't Exist");
        return;

    }

    User* u = &Library::mainLibrary().libraryUsers[loginType.second];
    if (loginType.first == 0){
        QMessageBox::information(this, "Success", "Welcome!\nLogged in as"
            " Regular User: " + QString::fromStdString(u->getUsername()));
    }

    else {
        QMessageBox::information(this, "Success", "Welcome!\nLogged in as "
                "Admin: " + QString::fromStdString(u->getUsername()));
    }
    mainwindow->setUser(u);
    this->hide();
    mainwindow->show();
}

