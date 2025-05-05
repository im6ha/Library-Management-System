#ifndef REMOVEWINDOW_H
#define REMOVEWINDOW_H

#include <QDialog>
#include "../library.h"

class LibraryManagementSystem;

namespace Ui {
class removeWindow;
}

class removeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit removeWindow(LibraryManagementSystem* mainWin, QWidget *parent = nullptr);
    ~removeWindow();

private slots:
    void on_back_clicked();

    void on_remove_clicked();

    void on_clear_clicked();

private:
    Ui::removeWindow *ui;
    LibraryManagementSystem *mainwindow;
};

#endif // REMOVEWINDOW_H
