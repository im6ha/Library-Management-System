#include "windows/reservationhistorywindow.h"
#include "qgraphicseffect.h"
#include "qlabel.h"
#include "ui_reservationhistorywindow.h"
#include "library.h"

reservationHistoryWindow::reservationHistoryWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reservationHistoryWindow)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System");
    QLabel *background = new QLabel(this);
    QPixmap pixmap("../../media/background.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();
    ui->historyTable->setColumnCount(8);
    ui->historyTable->setHorizontalHeaderLabels({"User ID", "Username", "Type", "Title", "Author",
                                                 "Pub. Year", "Quantity", "#Reservations"});

    for (int i = 0; i < Library::mainLibrary().reservationUsers.size(); i++) {
        User current_user = Library::mainLibrary().reservationUsers[i];
        for (int j = 0; j < current_user.indexOfReservedResources.size(); j++) {
            Resource current_resource = Library::mainLibrary().libraryResources
                                            [current_user.indexOfReservedResources[j].first]
                                            [current_user.indexOfReservedResources[j].second];
            pair <int,int> id = make_pair (current_user.indexOfReservedResources[j].first,current_user.indexOfReservedResources[j].second);

            addRow(current_user.getId(), QString::fromStdString(current_user.getUsername()),id,
                   QString::fromStdString(current_resource.getType()),
                   QString::fromStdString(current_resource.getTitle()),
                   QString::fromStdString(current_resource.getAuthor()),
                   current_resource.getPublicationYear(), current_resource.getQuantity(),
                   current_resource.getQuantity());
        }
    }


}

reservationHistoryWindow::~reservationHistoryWindow()
{
    delete ui;
}

void reservationHistoryWindow::addRow( int userId, QString username,pair<int,int> resourceId, QString type, QString title, QString author,
                                      int publicationYear, int quantity, int numberOfReservations ){

    int row = ui->historyTable->rowCount();
    ui->historyTable->insertRow(row);
    QString QID = "(" + QString :: number(resourceId.first) +","+ QString :: number(resourceId.second)+")";
    ui->historyTable->setItem(row, 0, new QTableWidgetItem(QString::number(userId)));
    ui->historyTable->setItem(row, 1, new QTableWidgetItem(username));
    ui->historyTable->setItem(row, 2, new QTableWidgetItem(QID));
    ui->historyTable->setItem(row, 3, new QTableWidgetItem(type));
    ui->historyTable->setItem(row, 4, new QTableWidgetItem(title));
    ui->historyTable->setItem(row, 5, new QTableWidgetItem(author));
    ui->historyTable->setItem(row, 6, new QTableWidgetItem(QString::number(publicationYear)));
    ui->historyTable->setItem(row, 7, new QTableWidgetItem(QString::number(quantity)));
    ui->historyTable->setItem(row, 8, new QTableWidgetItem(QString::number(numberOfReservations)));
}


void reservationHistoryWindow::on_back_clicked()
{
    this->hide();
}

