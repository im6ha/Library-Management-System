#include "windows/borrowinghistorywindow.h"
#include "user.h"
#include "library.h"
#include "qgraphicseffect.h"
#include "qlabel.h"
#include "ui_borrowinghistorywindow.h"

borrowingHistoryWindow::borrowingHistoryWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::borrowingHistoryWindow)
{
    ui->setupUi(this);
    setWindowTitle("Library Management System");
    QLabel *background = new QLabel(this);
    QPixmap pixmap(":/media/media/background.png");
    background->setPixmap(pixmap);
    background->setScaledContents(true);
    background->resize(this->size());
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(6);
    background->setGraphicsEffect(blur);
    background->lower();
    ui->borrowingTable->setColumnCount(7);
    ui->borrowingTable->setHorizontalHeaderLabels({ "User ID", "Username", "Type", "Title", "Author",
                                                 "Pub. Year", "Quantity"});
    if (!Library::mainLibrary().borrowingUsers.empty()){
        for (int i=0; i < Library::mainLibrary().borrowingUsers.size();i++){
            User current_user = Library::mainLibrary().borrowingUsers[i];
            for (int j =0; j < current_user.borrowedResources.size(); j++){
                Resource current_resource = Library::mainLibrary().libraryResources[current_user.borrowedResources[j].id.first]
                                                                        [current_user.borrowedResources[j].id.second];
                addRowBorrowingTable(current_user.getId(),QString :: fromStdString(current_user.getUsername()),QString :: fromStdString(current_resource.getType())
                                     , QString :: fromStdString(current_resource.getTitle()), QString::fromStdString(current_resource.getAuthor())
                                     , current_resource.getPublicationYear(), current_resource.getQuantity());
            }
        }
    }


    ui->historyTable->setColumnCount(8);
    ui->historyTable->setHorizontalHeaderLabels({ "User ID", "Username", "Type", "Title", "Author",
                                                   "Pub. Year", "Return Date", "On Time"});
    if (!Library :: mainLibrary().borrowingHistory.empty()){
        for (int i =0; i < Library :: mainLibrary().borrowingHistory.size(); i++){
            User current_user = Library::mainLibrary().borrowingHistory[i].borrowingUser;
            Resource current_resource = Library :: mainLibrary().borrowingHistory[i].borrowedResource;
            addRowHistoryTable(current_user.getId(), QString::fromStdString(current_user.getUsername()),QString::fromStdString(current_resource.getType()),
QString :: fromStdString(current_resource.getTitle()), QString::fromStdString(current_resource.getAuthor()), current_resource.getPublicationYear(),
                               Library::mainLibrary().borrowingHistory[i].returningDate, Library::mainLibrary().borrowingHistory[i].returnedOnTime);
        }
    }


}

void borrowingHistoryWindow::addRowBorrowingTable( int userId, QString username, QString type, QString title, QString author,
                                      int publicationYear, int quantity){

    int row = ui->borrowingTable->rowCount();
    ui->borrowingTable->insertRow(row);

    ui->borrowingTable->setItem(row, 0, new QTableWidgetItem(QString::number(userId)));
    ui->borrowingTable->setItem(row, 1, new QTableWidgetItem(username));
    ui->borrowingTable->setItem(row, 2, new QTableWidgetItem(type));
    ui->borrowingTable->setItem(row, 3, new QTableWidgetItem(title));
    ui->borrowingTable->setItem(row, 4, new QTableWidgetItem(author));
    ui->borrowingTable->setItem(row, 5, new QTableWidgetItem(QString::number(publicationYear)));
    ui->borrowingTable->setItem(row, 6, new QTableWidgetItem(QString::number(quantity)));
}

void borrowingHistoryWindow::addRowHistoryTable(int userId, QString username, QString type, QString title, QString author,
                                                int publicationYear, Date returnDate, bool onTime){
    int row = ui->historyTable->rowCount();
    ui->historyTable->insertRow(row);

    QString ontime = (onTime)? "Y":"n";

    ui->historyTable->setItem(row, 0, new QTableWidgetItem(QString::number(userId)));
    ui->historyTable->setItem(row, 1, new QTableWidgetItem(username));
    ui->historyTable->setItem(row, 2, new QTableWidgetItem(type));
    ui->historyTable->setItem(row, 3, new QTableWidgetItem(title));
    ui->historyTable->setItem(row, 4, new QTableWidgetItem(author));
    ui->historyTable->setItem(row, 5, new QTableWidgetItem(QString::number(publicationYear)));
    ui->historyTable->setItem(row, 6, new QTableWidgetItem(QString :: fromStdString(to_string(returnDate.getDay()) + "/" +
                                                          to_string(returnDate.getMonth()) + "/" + to_string(returnDate.getYear()))));
    ui->historyTable->setItem(row, 7, new QTableWidgetItem(ontime));
}

borrowingHistoryWindow::~borrowingHistoryWindow()
{
    delete ui;
}

void borrowingHistoryWindow::on_back_clicked()
{
    this->hide();
}
