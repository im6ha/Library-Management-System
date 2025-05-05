#ifndef USEREDITWINDOW_H
#define USEREDITWINDOW_H

#include <QDialog>
#include "../helper.h"

namespace Ui {
class userEditWindow;
}

class userEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit userEditWindow(QWidget *parent = nullptr);
    ~userEditWindow();

private slots:
    void on_makeAdmin_stateChanged(int arg1);

    void on_makeRegular_stateChanged(int arg1);

    void on_edit_clicked();

    void on_back_clicked();

private:
    Ui::userEditWindow *ui;
};

#endif // USEREDITWINDOW_H
