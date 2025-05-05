#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "../user.h"
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsBlurEffect>
#include <QMainWindow>


class LibraryManagementSystem;

namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginWindow(LibraryManagementSystem* main = nullptr, QWidget *parent = nullptr);
    ~loginWindow();

private slots:
    void on_isUsername_clicked();
    void on_isId_clicked();
    void on_signup_clicked();

    void on_login_clicked();


private:
    Ui::loginWindow *ui;
    LibraryManagementSystem* mainwindow;
    User* loggedInUser;
};

#endif // LOGINWINDOW_H
