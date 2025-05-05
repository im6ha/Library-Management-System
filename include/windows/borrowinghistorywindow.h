#ifndef BORROWINGHISTORYWINDOW_H
#define BORROWINGHISTORYWINDOW_H

#include "../date.h"
#include <QDialog>

namespace Ui {
class borrowingHistoryWindow;
}

class borrowingHistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit borrowingHistoryWindow(QWidget *parent = nullptr);
    ~borrowingHistoryWindow();

private slots:
    void on_back_clicked();

private:
    Ui::borrowingHistoryWindow *ui;
    void addRowBorrowingTable(int userId, QString username, QString type, QString title, QString author,
                int publicationYear, int quantity);
    void addRowHistoryTable(int userId, QString username, QString type, QString title, QString author,
                            int publicationYear, Date returnDate, bool onTime);

};

#endif // BORROWINGHISTORYWINDOW_H
