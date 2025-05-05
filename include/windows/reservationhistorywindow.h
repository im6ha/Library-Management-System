#ifndef RESERVATIONHISTORYWINDOW_H
#define RESERVATIONHISTORYWINDOW_H

#include <QDialog>
#include "../library.h"

namespace Ui {
class reservationHistoryWindow;
}

class reservationHistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit reservationHistoryWindow(QWidget *parent = nullptr);
    ~reservationHistoryWindow();

private slots:
    void on_back_clicked();

private:
    Ui::reservationHistoryWindow *ui;
    void addRow(int userId, QString username,pair<int,int> resourceId, QString type, QString title, QString author,
                int publicationYear, int quantity, int numberOfReservations );
};

#endif // RESERVATIONHISTORYWINDOW_H
