#include "windows/librarymanagementsystem.h"
#include "ui_librarymanagementsystem.h"


LibraryManagementSystem::LibraryManagementSystem(User* loggedInUser, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LibraryManagementSystem), currentUser(loggedInUser)
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

    if (currentUser && !currentUser->getAdmin()){
        ui->add->setEnabled(false);
        ui->remove->setEnabled(false);
        ui->edit->setEnabled(false);
        QMessageBox::information(this,"","Not All Feature Can be Accessed As Regular User");
    }
    addingwindow = nullptr;
    editwindow = nullptr;
    findwindow = nullptr;
    removewindow = nullptr;
    reservewindow = nullptr;
    borrowwindow = nullptr;
    loginwindow = nullptr;
    userwindow = nullptr;
    aboutwindow = nullptr;
    email = nullptr;
}

void LibraryManagementSystem::setUser(User* user)
{
    currentUser = user;
}

LibraryManagementSystem::~LibraryManagementSystem()
{
    if (addingwindow) delete addingwindow;
    if (editwindow) delete editwindow;
    if (findwindow) delete findwindow;
    if (removewindow) delete removewindow;
    if (borrowwindow) delete borrowwindow;
    if (loginwindow) delete loginwindow;
    if (userwindow) delete userwindow;
    delete ui;
}

void LibraryManagementSystem::on_add_clicked()
{
    if(currentUser && !currentUser->getAdmin()){
        QMessageBox::warning(this,"Not An Admin", "You Need to Be An Admin In Order To Access This Feature");
        return;
    }
    if(!addingwindow)
    addingwindow = new addWindow(this);
    this->hide();
    addingwindow->show();
}


void LibraryManagementSystem::on_edit_clicked()
{
    if(currentUser && !currentUser->getAdmin()){
        QMessageBox::warning(this,"Not An Admin", "You Need to Be An Admin In Order To Access This Feature");
        return;
    }
    if(!editwindow)
    editwindow = new editWindow(this);
    this->hide();
    editwindow->show();
}


void LibraryManagementSystem::on_remove_clicked()
{
    if(currentUser && !currentUser->getAdmin()){
        QMessageBox::warning(this,"Not An Admin", "You Need to Be An Admin In Order To Access This Feature");
        return;
    }
    if(!removewindow)
    removewindow = new removeWindow(this);
    this->hide();
    removewindow->show();
}




void LibraryManagementSystem::on_find_clicked()
{
    findwindow = new findWindow(this);
    findwindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    findwindow->show();
}


void LibraryManagementSystem::on_logout_clicked()
{
    loginwindow = new loginWindow(this);
    loginwindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    loginwindow->show();
}


void LibraryManagementSystem::on_user_clicked()
{

    userwindow = new userWindow(this,currentUser, this);
    userwindow->setAttribute(Qt::WA_DeleteOnClose);
    userwindow->setUser(currentUser);
    this->hide();
    userwindow->show();


}


void LibraryManagementSystem::on_reserve_clicked()
{
    if(!reservewindow)
        reservewindow = new reserveWindow(this, currentUser);
    this->hide();
    reservewindow->show();
}


void LibraryManagementSystem::on_borrow_clicked()
{
    if (borrowwindow)
        delete borrowwindow;

    borrowwindow = new borrowWindow(currentUser,this);
    this->hide();
    borrowwindow->show();
}

void LibraryManagementSystem::on_save_clicked()
{
    Helper::save();
}


void LibraryManagementSystem::on_about_clicked()
{
    if(aboutwindow)
        delete aboutwindow;

    aboutwindow = new about(this,currentUser);
    this->hide();
    aboutwindow->show();
}


void LibraryManagementSystem::on_email_clicked()
{
    if(email)
        delete email;

    if(currentUser && !currentUser->getAdmin()){
        QMessageBox::warning(this,"Not An Admin", "You Need to Be An Admin In Order To Access This Feature");
        return;
    }
    email = new emailwindow;
    this->hide();
    email->show();
}

