#ifndef RESERVEWINDOW_H
#define RESERVEWINDOW_H

#include <QDialog>
#include "../library.h"
#include "reservationhistorywindow.h"


class LibraryManagementSystem;

namespace Ui {
class reserveWindow;
}

class reserveWindow : public QDialog
{
    Q_OBJECT

public:
    explicit reserveWindow(LibraryManagementSystem* mainWin, User* loggedInUser, QWidget *parent = nullptr);
    ~reserveWindow();

private slots:
    void on_currentUser_stateChanged(int arg1);

    void on_isId_clicked();

    void on_isUsername_clicked();

    void on_find_clicked();

    void on_isResource_stateChanged(int arg1);

    void on_isID_stateChanged(int arg1);

    void on_back_clicked();

    void on_history_clicked();

    void on_delete_2_clicked();

private:
    Ui::reserveWindow *ui;
    User* currentUser;
    reservationHistoryWindow* history;
    LibraryManagementSystem *mainwindow;
};

#endif // RESERVEWINDOW_H

