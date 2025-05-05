#ifndef USERADDWINDOW_H
#define USERADDWINDOW_H

#include <QDialog>
#include "../helper.h"

namespace Ui {
class userAddWindow;
}

class userAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userAddWindow(QWidget *parent = nullptr);
    ~userAddWindow();

private slots:
    void on_signup_clicked();

    void on_back_clicked();

private:
    Ui::userAddWindow *ui;
};

#endif // USERADDWINDOW_H
