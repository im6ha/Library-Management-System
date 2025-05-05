#ifndef EMAILWINDOW_H
#define EMAILWINDOW_H
#include "../library.h"

#include <QDialog>

class LibraryManagementSystem;

namespace Ui {
class emailwindow;
}

class emailwindow : public QDialog
{
    Q_OBJECT

public:
    explicit emailwindow(QWidget *parent = nullptr);
    ~emailwindow();

private slots:
    void on_add_clicked();

    void on_delete_2_clicked();

    void on_send_clicked();

    void on_back_clicked();

private:
    Ui::emailwindow *ui;
    void printEmails();

    LibraryManagementSystem* mainWindow;
};

#endif // EMAILWINDOW_H
