#ifndef ADDWINDOW_H
#define ADDWINDOW_H
#include <string>
#include <QString>
#include <QDialog>
#include <QMessageBox>
#include<QMainWindow>
#include <QDebug>
#include "../library.h"
using namespace std;

class LibraryManagementSystem;

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(LibraryManagementSystem* mainWin, QWidget *parent = nullptr);
    ~addWindow();
    static Resource lastAdded;

private slots:
    void on_add_clicked();

    void on_reset_clicked();

    void on_back_clicked();

private:
    Ui::addWindow *ui;
    LibraryManagementSystem* mainwindow;

};

#endif // ADDWINDOW_H
