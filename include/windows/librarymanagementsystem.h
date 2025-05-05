#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H
#include "library.h"
#include "windows/addwindow.h"
#include "windows/editwindow.h"
#include "windows/removewindow.h"
#include "windows/findwindow.h"
#include "windows/loginwindow.h"
#include "windows/reservewindow.h"
#include "windows/userwindow.h"
#include "windows/borrowwindow.h"
#include "windows/about.h"
#include "windows/emailwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LibraryManagementSystem;
}
QT_END_NAMESPACE

class LibraryManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibraryManagementSystem(User* loggedInUser = nullptr, QWidget *parent = nullptr);
    ~LibraryManagementSystem();

    void setUser(User* user);

private slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_remove_clicked();
    void on_find_clicked();
    void on_logout_clicked();

    void on_user_clicked();

    void on_reserve_clicked();

    void on_borrow_clicked();

    void on_save_clicked();

    void on_about_clicked();

    void on_email_clicked();

private:
    Ui::LibraryManagementSystem *ui;
    User* currentUser;
    addWindow* addingwindow;
    editWindow* editwindow;
    removeWindow* removewindow;
    findWindow* findwindow;
    loginWindow* loginwindow;
    userWindow* userwindow;
    borrowWindow* borrowwindow;
    reserveWindow* reservewindow;
    about* aboutwindow;
    emailwindow* email;
};

#endif // LIBRARYMANAGEMENTSYSTEM_H

