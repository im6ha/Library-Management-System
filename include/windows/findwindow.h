#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "../library.h"
#include "qtablewidget.h"

class LibraryManagementSystem;

namespace Ui {
class findWindow;
}

class findWindow : public QDialog
{
    Q_OBJECT

public:
    explicit findWindow(LibraryManagementSystem* mainWin, QWidget *parent = nullptr);


    ~findWindow();

private slots:
    void addRow(QString id, QString type, QString title, QString author, int publicationYear,
                int quantity, char borrowed, int numberOfReservations );

    void print2DLibrary();
    void print1DLibrary(vector <Resource>);

    void reverseTable(QTableWidget* table);

    void on_isPublication_stateChanged(int arg1);


    void on_isAuthor_stateChanged(int arg1);

    void on_isResource_stateChanged(int arg1);

    void on_isTitle_stateChanged(int arg1);

    void on_isID1_stateChanged(int arg1);

    void on_isID2_stateChanged(int arg1);

    void on_back_clicked();

    void on_find_clicked();

    void on_unsort_clicked(bool checked);

    void on_author_clicked(bool checked);

    void on_title_clicked(bool checked);

    void on_publicationYear_clicked(bool checked);

    void on_quantity_clicked(bool checked);

    void on_reservation_clicked(bool checked);

    void on_availability_clicked(bool checked);

    void on_reverseOrder_clicked(bool checked);

private:
    Ui::findWindow *ui;
    LibraryManagementSystem* mainwindow;
};

#endif // FINDWINDOW_H
