#include "windows/userwindow.h"
#include "ui_userwindow.h"
#include "windows/useraddwindow.h"
#include"windows/usereditwindow.h"
#include"windows/userremovewindow.h"
#include "windows/librarymanagementsystem.h"



userWindow :: userWindow( LibraryManagementSystem* mainWin, User* loggedInUser, QWidget* parent)
    : QDialog(parent), ui(new Ui::userWindow), currentUser(loggedInUser), mainwindow(mainWin),
    userremovewindow(nullptr), usereditwindow(nullptr), useraddwindow(nullptr)
{

    ui->setupUi(this);
    QLabel *background = new QLabel(this);
    QPixmap pixmap(":/media/media/background.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();
    setWindowTitle("Library Management System");
userremovewindow = new userRemoveWindow(nullptr, this);
    usereditwindow = new userEditWindow(this);
    useraddwindow = new userAddWindow(this);

    ui->usersDisplay->setColumnCount(6);
    ui->usersDisplay->setHorizontalHeaderLabels({"ID", "Username", "Password",
                                                "isAdmin", "#Borrowed Items", "# Reserved Items"});

    ui->usersDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if (currentUser && !currentUser->getAdmin()){
        ui->add->setEnabled(false);
        ui->remove->setEnabled(false);
        ui->edit->setEnabled(false);
        ui->isId->setChecked(true);
        QMessageBox :: warning (this,"Regular User", "You Need to Enter an Admin's Account Information");
    }

    else if (currentUser && currentUser->getAdmin()) {
        ui->isId->setEnabled(false);
        ui->isUsername->setEnabled(false);
        ui->username->setEnabled(false);
        ui->password->setEnabled(false);
        ui->id->setEnabled(false);
        ui->login->setEnabled(false);
        on_displayAll_clicked();
    }
}

void userWindow::setUser(User* user)
{
    currentUser = user;
}

userWindow::~userWindow()
{
    if (useraddwindow) delete useraddwindow;
    if (usereditwindow) delete usereditwindow;
    if (userremovewindow) delete userremovewindow;
    delete ui;
}

void userWindow :: addRow(int id, QString username, QString password,
            bool isAdmin, int borrowedItems, int reservedItems){
    int row = ui->usersDisplay->rowCount();
    ui->usersDisplay->insertRow(row);

    ui->usersDisplay->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    ui->usersDisplay->setItem(row, 1, new QTableWidgetItem(username));
    ui->usersDisplay->setItem(row, 2, new QTableWidgetItem(password));
    ui->usersDisplay->setItem(row, 3, new QTableWidgetItem(isAdmin ? "Yes" : "No"));
    ui->usersDisplay->setItem(row, 4, new QTableWidgetItem(QString::number(borrowedItems)));
    ui->usersDisplay->setItem(row, 5, new QTableWidgetItem(QString::number(reservedItems)));
}
void userWindow::on_login_clicked()
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
    case 0:
        QMessageBox:: warning(this, "Regular Account", "The Enterred Information "
                                    "Doesn't Match an Admin's Account");
        return;
    case -1:
        QMessageBox:: warning(this, "Wrong Pasword", "The Enterred Password Doesn't Match The Username");
        return;
    case -2:
        QMessageBox:: warning(this, "Wrong Username", "The Enterred Username Doesn't Exist");
        return;
    }

    if (loginType.first==1){
        ui->add->setEnabled(true);
        ui->remove->setEnabled(true);
        ui->edit->setEnabled(true);
        currentUser = &Library::mainLibrary().libraryUsers[loginType.second];
        QMessageBox :: information (this,"Success", "Successfully Logged In as An Admin User For This Window");
        for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
            User currentUser = Library::mainLibrary().libraryUsers[i];
            addRow(currentUser.getId(), QString :: fromStdString( currentUser.getUsername()),
                   QString :: fromStdString(currentUser.getPassword()), currentUser.getAdmin(),
                   currentUser.borrowedResources.size(),
                   currentUser.indexOfReservedResources.size());
        }
    }

}


void userWindow::on_edit_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    usereditwindow->show();
}


void userWindow::on_add_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    useraddwindow->show();
}


void userWindow::on_remove_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    userremovewindow->show();
}


void userWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void userWindow::on_displayReserving_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    ui->usersDisplay->setRowCount(0);
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        User currentUser = Library::mainLibrary().libraryUsers[i];
        if (!currentUser.indexOfReservedResources.empty()){

            addRow(currentUser.getId(), QString :: fromStdString( currentUser.getUsername()),
                   QString :: fromStdString(currentUser.getPassword()), currentUser.getAdmin(),
                   currentUser.borrowedResources.size(),
                   currentUser.indexOfReservedResources.size());
        }
    }
}




void userWindow::on_displayBorrowin_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    ui->usersDisplay->setRowCount(0);
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        User currentUser = Library::mainLibrary().libraryUsers[i];
        if (!currentUser.borrowedResources.empty()){

            addRow(currentUser.getId(), QString :: fromStdString( currentUser.getUsername()),
                   QString :: fromStdString(currentUser.getPassword()), currentUser.getAdmin(),
                   currentUser.borrowedResources.size(),
                   currentUser.indexOfReservedResources.size());
        }
    }
}


void userWindow::on_displayAll_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox::warning(this,"Error", "This Feature Can't Be Accessed Without Logging in As Admin User");
        return;
    }
    ui->usersDisplay->setRowCount(0);
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        User currentUser = Library::mainLibrary().libraryUsers[i];
        addRow(currentUser.getId(), QString :: fromStdString( currentUser.getUsername()),
               QString :: fromStdString(currentUser.getPassword()), currentUser.getAdmin(),
               currentUser.borrowedResources.size(),
               currentUser.indexOfReservedResources.size());
    }
}

