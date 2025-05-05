#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include "../user.h"
#include "userremovewindow.h"
#include "useraddwindow.h"
#include "usereditwindow.h"
#include <QMessageBox>

class LibraryManagementSystem;

namespace Ui {
class userWindow;
}

class userWindow : public QDialog
{
    Q_OBJECT

public:
     userWindow( LibraryManagementSystem* mainWin, User* loggedInUser= nullptr, QWidget* parent=nullptr);
    void setUser(User* user);
    ~userWindow();

private slots:
    void on_login_clicked();

    void on_edit_clicked();

    void on_add_clicked();

    void on_remove_clicked();

    void on_back_clicked();

    void on_displayBorrowin_clicked();

    void on_displayReserving_clicked();

    void on_displayAll_clicked();

private:
    Ui::userWindow *ui;
    User* currentUser;
    void addRow(int id, QString username, QString password,
                bool isAdmin, int borrowedItems, int reservedItems);
    userRemoveWindow* userremovewindow;
    userEditWindow* usereditwindow;
    userAddWindow* useraddwindow;
    LibraryManagementSystem* mainwindow;
};

#endif // USERWINDOW_H
