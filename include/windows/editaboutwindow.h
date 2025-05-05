#ifndef EDITABOUTWINDOW_H
#define EDITABOUTWINDOW_H

#include <QDialog>
#include "../library.h"


namespace Ui {
class editAboutWindow;
}

class editAboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editAboutWindow(QWidget *parent = nullptr);
    ~editAboutWindow();

private slots:

    void on_sunday_checkStateChanged(const Qt::CheckState &arg1);

    void on_monday_checkStateChanged(const Qt::CheckState &arg1);

    void on_tuesday_checkStateChanged(const Qt::CheckState &arg1);

    void on_wednesday_checkStateChanged(const Qt::CheckState &arg1);

    void on_thursday_checkStateChanged(const Qt::CheckState &arg1);

    void on_friday_checkStateChanged(const Qt::CheckState &arg1);

    void on_saturday_checkStateChanged(const Qt::CheckState &arg1);

    void on_edit_clicked();

    void on_addEvent_clicked();

    void on_deleteEvent_clicked();


    void on_back_clicked();

private:
    Ui::editAboutWindow *ui;
    void refreshTable();
};

#endif // EDITABOUTWINDOW_H
