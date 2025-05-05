#ifndef BORROWWINDOW_H
#define BORROWWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include "../user.h"
#include "borrowinghistorywindow.h"

class LibraryManagementSystem;
class reserveWindow;

namespace Ui {
class borrowWindow;
}

class borrowWindow : public QDialog
{
    Q_OBJECT

public:
    explicit borrowWindow(User* user, LibraryManagementSystem* mainwindow, QWidget *parent = nullptr);
    ~borrowWindow();

private slots:
    void on_useLoggedin_stateChanged(int arg1);

    void on_isId_clicked();

    void on_isUsername_clicked();

    void on_byResource_stateChanged(int arg1);

    void on_byId_stateChanged(int arg1);

    void on_borrow_clicked();

    void on_renew_clicked();

    void on_return_2_clicked();

    void on_currentDate_stateChanged(int arg1);

    void on_back_clicked();

    void on_hisotry_clicked();

private:
    Ui::borrowWindow *ui;
    User* currentUser;
    LibraryManagementSystem* mainwindow;
    borrowingHistoryWindow* history;
    reserveWindow* reservewindow;

};

#endif // BORROWWINDOW_H
