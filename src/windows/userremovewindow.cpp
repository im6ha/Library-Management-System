#include "windows/userremovewindow.h"
#include "windows/librarymanagementsystem.h"
#include "ui_userremovewindow.h"
#include "library.h"

userRemoveWindow::userRemoveWindow(loginWindow* loginWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::userRemoveWindow), loginwindow(loginWin)
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

userRemoveWindow::~userRemoveWindow()
{
    delete ui;
}

void userRemoveWindow::on_clear_clicked()
{
    if (Library::mainLibrary().libraryUsers.empty()){
        QMessageBox :: warning(this,"", "No Users");
        return;
    }
    if(Helper :: confirmAction(this)){
        Library::mainLibrary().libraryUsers.clear();
        QMessageBox :: information(this,"Success", "All Users Deleted");
        this->hide();
        loginwindow->show();
    }
}


void userRemoveWindow::on_remove_clicked()
{
    if (!ui->isId->isChecked() && !ui->isUsername->isChecked()){
        QMessageBox::warning(this,"","You Need to Either Specify the ID or Username");
        return;
    }

    if (ui->isUsername->isChecked() && ui->username->text().isEmpty()){
        QMessageBox::warning(this,"","You Need to Fill Checked Fields");
        return;
    }

    if (ui->isUsername->isChecked()){
        if(Library::mainLibrary().deleteUser(ui->username->text().toStdString())){
            QMessageBox :: information(this,"Success", "User Deleted SUccessfully");
            return;
        }
        else {
            QMessageBox :: warning (this,"", "User Not Found");
            return;
        }
    }
    else if (ui->isId->isChecked()){
        if(Library::mainLibrary().deleteUser(ui->id->value())){
            QMessageBox :: information(this,"Success", "User Deleted SUccessfully");
            return;
        }
        else {
            QMessageBox :: warning (this,"", "User Not Found");
            return;
        }
    }
}


void userRemoveWindow::on_back_clicked()
{
    this->hide();
}

