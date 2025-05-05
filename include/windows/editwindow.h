#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMessageBox>
#include <QDialog>
#include "../library.h"

class LibraryManagementSystem;

namespace Ui {
class editWindow;
}

class editWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editWindow(LibraryManagementSystem* mainWin, QWidget *parent = nullptr);
    ~editWindow();

private slots:
    void on_edit_clicked();

    void on_isAuthor_stateChanged(int arg1);

    void on_isTitle_stateChanged(int arg1);

    void on_isQuantity_stateChanged(int arg1);

    void on_isType_stateChanged(int arg1);

    void on_isPublicationYear_stateChanged(int arg1);

    void on_reset_clicked();

    void on_back_clicked();

private:
    Ui::editWindow *ui;
    LibraryManagementSystem *mainwindow;
};

#endif // EDITWINDOW_H
