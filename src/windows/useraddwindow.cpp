#include "windows/useraddwindow.h"
#include "library.h"
#include "qgraphicseffect.h"
#include "qlabel.h"
#include "ui_useraddwindow.h"
#include <QMessageBox>

userAddWindow::userAddWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userAddWindow)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System");
    QLabel *background = new QLabel(this);
    QPixmap pixmap("../../media/background.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();
}

userAddWindow::~userAddWindow()
{
    delete ui;
}

void userAddWindow::on_signup_clicked()
{
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


    Library::mainLibrary().addUser(User(username,password,ui->isAdmin->isChecked()));
    QMessageBox::information(this, "Success", "User Added Successfully\nUsername: " +
                                                  QString::fromStdString(Library::mainLibrary().libraryUsers.back().getUsername()) +
                                                  "\nID: " + QString::number(Library::mainLibrary().libraryUsers.back().getId()));

    this ->hide();
}


void userAddWindow::on_back_clicked()
{
    this->hide();
}

