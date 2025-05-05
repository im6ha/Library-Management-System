#include "windows/about.h"
#include "qgraphicseffect.h"
#include "ui_about.h"
#include "windows/librarymanagementsystem.h"


about::about(LibraryManagementSystem* mainWin, User* user, QWidget *parent)
    : QDialog(parent),
    currentUser(user),
    mainwindow(mainWin),
    ui(new Ui::about)
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

    ui->eventsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->openingSchedule->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refresh();
    editaboutwindow = nullptr;

}

about::~about()
{
    delete ui;
}

void about :: refresh(){
    ui->ampm->setChecked(false);
    Library::mainLibrary().refreshEvents();
    on_ampm_stateChanged(ui->ampm->checkState());
    ui->openingSchedule->setColumnCount(2);
    ui->openingSchedule->setHorizontalHeaderLabels({"Opening Time - Closing Time", "Time Open"});
    ui->openingSchedule->setRowCount(7);

    ui->openingSchedule->setVerticalHeaderLabels({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"});
    about::openingScheduleTable(ui->ampm->checkState());




    if(Library::mainLibrary().libraryEvents.empty()){
        ui->eventsTable->setRowCount(1);
        ui->eventsTable->setColumnCount(1);
        QTableWidgetItem *item = new QTableWidgetItem("No Events Available");
        item->setTextAlignment(Qt::AlignCenter);
        ui->eventsTable->setItem(0, 0, item);
    }
    else{
        ui->eventsTable->setRowCount(Library::mainLibrary().libraryEvents.size());
        ui->eventsTable->setColumnCount(4);
        ui->eventsTable->setHorizontalHeaderLabels({"Event's Title", "Event's Description", "Starting Date & Time", "Ending Date & Time"});
        for (int i=0; i<Library::mainLibrary().libraryEvents.size();i++){
            string startingTime = (ui->ampm->isChecked())? Library::mainLibrary().libraryEvents[i].startingTime.toStringAMPM() :
                                      Library::mainLibrary().libraryEvents[i].startingTime.toString();

            QString starting = QString::fromStdString(Library::mainLibrary().libraryEvents[i].startingDate.toString() + "   "+startingTime );

            string closingTime = (ui->ampm->isChecked())? Library::mainLibrary().libraryEvents[i].endingTime.toStringAMPM() :
                                     Library::mainLibrary().libraryEvents[i].endingTime.toString();

            QString closing = QString::fromStdString(Library::mainLibrary().libraryEvents[i].endingDate.toString() + "   "+closingTime );

            ui->eventsTable->setItem(i,0, new QTableWidgetItem(QString :: fromStdString(Library::mainLibrary().libraryEvents[i].title)));
            ui->eventsTable->setItem(i,1, new QTableWidgetItem(QString :: fromStdString(Library::mainLibrary().libraryEvents[i].description)));
            ui->eventsTable->setItem(i,2, new QTableWidgetItem(starting));
            ui->eventsTable->setItem(i,3, new QTableWidgetItem(closing));

        }
    }
}

void about::on_ampm_stateChanged(int state)
{
        for (int i = 0; i < 7; i++) {
            QString openingTime = (state == Qt::Checked)? QString::fromStdString( Library::mainLibrary().openingTimes[i].toStringAMPM()) :
            QString::fromStdString( Library::mainLibrary().openingTimes[i].toString() );

            QString closingTime =  QString::fromStdString( Library::mainLibrary().closingTimes[i].toStringAMPM() );
            QString isOpen = (Library::mainLibrary().isOpen[i]) ? "Yes" : "No";
            ui->openingSchedule->setItem(i, 0, new QTableWidgetItem(openingTime+" - "+closingTime));
            ui->openingSchedule->setItem(i, 1, new QTableWidgetItem(isOpen));
        }
}


void about::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void about::on_edit_clicked()
{
    if (!currentUser->getAdmin()){
        QMessageBox ::warning(this,"","This Feature is Only Available for Admins");
        return;
    }
    if(editaboutwindow)
        delete editaboutwindow;

    editaboutwindow = new editAboutWindow();
    editaboutwindow->show();
}

void about::openingScheduleTable(int state) {
    for (int i = 0; i < 7; i++) {
        Time opening = Library::mainLibrary().openingTimes[i];
        Time closing = Library::mainLibrary().closingTimes[i];
        bool isOpen = Library::mainLibrary().isOpen[i];

        QString openingStr = (state == Qt::Checked) ?
                                 QString::fromStdString(opening.toStringAMPM()) :
                                 QString::fromStdString(opening.toString());

        QString closingStr = (state == Qt::Checked) ?
                                 QString::fromStdString(closing.toStringAMPM()) :
                                 QString::fromStdString(closing.toString());

        ui->openingSchedule->setItem(i, 0, new QTableWidgetItem(openingStr + " - " + closingStr));
        ui->openingSchedule->setItem(i, 1, new QTableWidgetItem(isOpen ? "Yes" : "No"));
    }
}

