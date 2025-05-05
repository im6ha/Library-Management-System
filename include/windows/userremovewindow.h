#ifndef USERREMOVEWINDOW_H
#define USERREMOVEWINDOW_H

#include <QDialog>
#include "loginwindow.h"
class loginWindow;
namespace Ui {
class userRemoveWindow;
}

class userRemoveWindow : public QDialog
{
    Q_OBJECT

public:
explicit userRemoveWindow(loginWindow* loginWin = nullptr, QWidget *parent = nullptr);
    ~userRemoveWindow();

private slots:
    void on_clear_clicked();

    void on_remove_clicked();

    void on_back_clicked();

private:
    Ui::userRemoveWindow *ui;
    loginWindow *loginwindow;
};

#endif // USERREMOVEWINDOW_H
