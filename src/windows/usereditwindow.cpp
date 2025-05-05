#include "windows/usereditwindow.h"
#include "qgraphicseffect.h"
#include "qlabel.h"
#include "ui_usereditwindow.h"
#include "library.h"
#include "QMessageBox"
using namespace std;

userEditWindow::userEditWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userEditWindow)
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

userEditWindow::~userEditWindow()
{
    delete ui;
}

void userEditWindow::on_makeAdmin_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->makeRegular->setChecked(false);
    }
}

void userEditWindow::on_makeRegular_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->makeAdmin->setChecked(false);
    }
}


void userEditWindow::on_edit_clicked()
{
    bool changed = false;

    if (!ui->isUsername->isChecked() && !ui->isId->isChecked()){
        QMessageBox:: warning(this,"","No User's Information Enterred");
        return;
    }

    if ((ui->isUsername->isChecked() && ui->username->text().isEmpty()) ){
        QMessageBox:: warning(this,"","Identifier Field Must Not be Empty");
        return;
    }

    if (!ui->changePass->isChecked()&&!ui->changeUser->isChecked()&&!ui->makeAdmin->isChecked()&&
        !ui->makeRegular->isChecked()){
        QMessageBox:: warning(this,"","No Changes To Apply");
        return;
    }

    string username =ui->newUsername->text().toStdString();
    string password= ui->newPass->text().toStdString();
    User test;
    User :: currentId--;
    int errorCheck = test.setUsername(username);
    switch (errorCheck){
    case -1:
        QMessageBox :: warning(this,"", "New Username Can't Start With a Number");
        return;
    case -2:
        QMessageBox :: warning(this,"", "New Username Must Only Contain Alphabetic or"
                                        "Numeric Characters");
        return;
    case -3:
        QMessageBox :: warning(this,"", "New Username Can't Exceed 10 Characters");
        return;
    case -4:
        QMessageBox :: warning(this,"", "New Username Already Taken");
        return;
    }

    errorCheck = test.setPassword(password);
    switch (errorCheck){
    case -1:
        QMessageBox :: warning(this,"", "New Password Can't be Less Than 4 Characters");
        return;
    case -2:
        QMessageBox :: warning(this,"", "New Password Can't Exceed 12 Characters");
        return;
    case -3:
        QMessageBox :: warning(this,"", "New Password Must Contain a Number");
        return;
    case -4:
        QMessageBox :: warning(this,"", "New Password Must Contain an Alphabetic Character");
        return;
    case -5:
        QMessageBox :: warning(this,"", "New Password Contains Unallowed Special Characters");
        return;
    }

    int index;
    if (ui->isUsername->isChecked()) {
        index = Library::mainLibrary().findUser(ui->username->text().toStdString());
    } else {
        index = Library::mainLibrary().findUser(ui->id->value());
    }

    if (index == -1){
        QMessageBox:: warning(this,"","The User Doesn't Exist");
        return;
    }


    if (Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeAdmin &&
        (ui->changeUser->isChecked() || ui->changePass->isChecked())){
        QMessageBox:: warning(this,"","The User is Already an Admin\n"
                                       "Other Information Will Be Changed");
    }
    else if (Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeAdmin &&
             !(ui->changeUser->isChecked() || ui->changePass->isChecked())){
        QMessageBox:: warning(this,"","The User is Already an Admin\n");
    }

    else if (Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeAdmin) {
        Library::mainLibrary().libraryUsers[index].setAdmin(true);
        changed = true;
    }


    else if (Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeRegular &&
        (ui->changeUser->isChecked() || ui->changePass->isChecked())){
        QMessageBox:: warning(this,"","The User is Already a Regular User\n"
                                       "Other Information Will Be Changed");
    }
    else if (!Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeRegular &&
        !(ui->changeUser->isChecked() || ui->changePass->isChecked())){
        QMessageBox:: warning(this,"","The User is Already a Regular User\n");
    }
    else if (Library::mainLibrary().libraryUsers[index].getAdmin() && ui->makeRegular) {
        Library::mainLibrary().libraryUsers[index].setAdmin(false);
        changed = true;
    }
    if (ui->changeUser->isChecked()){
        Library::mainLibrary().libraryUsers[index].setUsername(ui->newUsername->text().toStdString());
        changed = true;
    }

    if (ui->changePass->isChecked()){
        Library::mainLibrary().libraryUsers[index].setPassword(ui->newPass->text().toStdString());
        changed = true;
    }

    if (changed)
        QMessageBox :: information (this,"Success", "Changes Successfully Done");

}


void userEditWindow::on_back_clicked()
{
    this->hide();
}

