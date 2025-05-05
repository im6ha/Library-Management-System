#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "../library.h"
#include "editaboutwindow.h"

class LibraryManagementSystem;

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(LibraryManagementSystem* mainWin,User* currentUser,QWidget *parent = nullptr);
    void openingScheduleTable(int state);
    ~about();

private slots:
    void on_ampm_stateChanged(int arg1);

    void on_back_clicked();

    void on_edit_clicked();

private:
    User* currentUser;
    LibraryManagementSystem* mainwindow;
    editAboutWindow* editaboutwindow;
    Ui::about *ui;

    void refresh();
};

#endif // ABOUT_H
