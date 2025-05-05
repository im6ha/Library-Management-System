#include "windows/editaboutwindow.h"
#include "qgraphicseffect.h"
#include "ui_editaboutwindow.h"

editAboutWindow::editAboutWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editAboutWindow)
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

    ui->events->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->eventStatringTime->setDateTime(QDateTime::currentDateTime());
    ui->eventClosingTime->setDateTime(QDateTime::currentDateTime().addDays(7));

    ui->sunday->setChecked(Library::mainLibrary().isOpen[0]);
    ui->monday->setChecked(Library::mainLibrary().isOpen[1]);
    ui->tuesday->setChecked(Library::mainLibrary().isOpen[2]);
    ui->wednesday->setChecked(Library::mainLibrary().isOpen[3]);
    ui->thursday->setChecked(Library::mainLibrary().isOpen[4]);
    ui->friday->setChecked(Library::mainLibrary().isOpen[5]);
    ui->saturday->setChecked(Library::mainLibrary().isOpen[6]);

    ui->openingSun->setTime(QTime(Library::mainLibrary().openingTimes[0].getHours(), Library::mainLibrary().openingTimes[0].getMinutes()));
    ui->closingSun->setTime(QTime(Library::mainLibrary().closingTimes[0].getHours(), Library::mainLibrary().closingTimes[0].getMinutes()));

    ui->openingMon->setTime(QTime(Library::mainLibrary().openingTimes[1].getHours(), Library::mainLibrary().openingTimes[1].getMinutes()));
    ui->closingMon->setTime(QTime(Library::mainLibrary().closingTimes[1].getHours(), Library::mainLibrary().closingTimes[1].getMinutes()));

    ui->openingTues->setTime(QTime(Library::mainLibrary().openingTimes[2].getHours(), Library::mainLibrary().openingTimes[2].getMinutes()));
    ui->closingTues->setTime(QTime(Library::mainLibrary().closingTimes[2].getHours(), Library::mainLibrary().closingTimes[2].getMinutes()));

    ui->openingWednes->setTime(QTime(Library::mainLibrary().openingTimes[3].getHours(), Library::mainLibrary().openingTimes[3].getMinutes()));
    ui->closingWednes->setTime(QTime(Library::mainLibrary().closingTimes[3].getHours(), Library::mainLibrary().closingTimes[3].getMinutes()));

    ui->openingThurs->setTime(QTime(Library::mainLibrary().openingTimes[4].getHours(), Library::mainLibrary().openingTimes[4].getMinutes()));
    ui->closingThurs->setTime(QTime(Library::mainLibrary().closingTimes[4].getHours(), Library::mainLibrary().closingTimes[4].getMinutes()));

    ui->openingFri->setTime(QTime(Library::mainLibrary().openingTimes[5].getHours(), Library::mainLibrary().openingTimes[5].getMinutes()));
    ui->closingFri->setTime(QTime(Library::mainLibrary().closingTimes[5].getHours(), Library::mainLibrary().closingTimes[5].getMinutes()));

    ui->openingSatur->setTime(QTime(Library::mainLibrary().openingTimes[6].getHours(), Library::mainLibrary().openingTimes[6].getMinutes()));
    ui->closingSatur->setTime(QTime(Library::mainLibrary().closingTimes[6].getHours(), Library::mainLibrary().closingTimes[6].getMinutes()));


    refreshTable();
}

editAboutWindow::~editAboutWindow()
{
    delete ui;
}



void editAboutWindow::on_sunday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->sundayGroup->setEnabled(true);
        ui->openingSun->setTime(QTime(Library::mainLibrary().openingTimes[0].getHours(), Library::mainLibrary().openingTimes[0].getMinutes()));
        ui->closingSun->setTime(QTime(Library::mainLibrary().closingTimes[0].getHours(), Library::mainLibrary().closingTimes[0].getMinutes()));
    }
    else{
        ui->sundayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_monday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->mondayGroup->setEnabled(true);
        ui->openingMon->setTime(QTime(Library::mainLibrary().openingTimes[1].getHours(), Library::mainLibrary().openingTimes[1].getMinutes()));
        ui->closingMon->setTime(QTime(Library::mainLibrary().closingTimes[1].getHours(), Library::mainLibrary().closingTimes[1].getMinutes()));

    }
    else{
        ui->mondayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_tuesday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->tuesdayGroup->setEnabled(true);
        ui->openingTues->setTime(QTime(Library::mainLibrary().openingTimes[2].getHours(), Library::mainLibrary().openingTimes[2].getMinutes()));
        ui->closingTues->setTime(QTime(Library::mainLibrary().closingTimes[2].getHours(), Library::mainLibrary().closingTimes[2].getMinutes()));
    }
    else{
        ui->tuesdayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_wednesday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->wednesdayGroup->setEnabled(true);
        ui->openingWednes->setTime(QTime(Library::mainLibrary().openingTimes[3].getHours(), Library::mainLibrary().openingTimes[3].getMinutes()));
        ui->closingWednes->setTime(QTime(Library::mainLibrary().closingTimes[3].getHours(), Library::mainLibrary().closingTimes[3].getMinutes()));
    }
    else{
        ui->wednesdayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_thursday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->thursdayGroup->setEnabled(true);
        ui->openingThurs->setTime(QTime(Library::mainLibrary().openingTimes[4].getHours(), Library::mainLibrary().openingTimes[4].getMinutes()));
        ui->closingThurs->setTime(QTime(Library::mainLibrary().closingTimes[4].getHours(), Library::mainLibrary().closingTimes[4].getMinutes()));
    }
    else{
        ui->thursdayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_friday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->fridayGroup->setEnabled(true);
        ui->openingFri->setTime(QTime(Library::mainLibrary().openingTimes[5].getHours(), Library::mainLibrary().openingTimes[5].getMinutes()));
        ui->closingFri->setTime(QTime(Library::mainLibrary().closingTimes[5].getHours(), Library::mainLibrary().closingTimes[5].getMinutes()));
    }
    else{
        ui->fridayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_saturday_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked){
        ui->saturdayGroup->setEnabled(true);
        ui->openingSatur->setTime(QTime(Library::mainLibrary().openingTimes[6].getHours(), Library::mainLibrary().openingTimes[6].getMinutes()));
        ui->closingSatur->setTime(QTime(Library::mainLibrary().closingTimes[6].getHours(), Library::mainLibrary().closingTimes[6].getMinutes()));
    }
    else{
        ui->saturdayGroup->setEnabled(false);
    }
}


void editAboutWindow::on_edit_clicked()
{
    Time sundayOpening(ui->openingSun->time()), sundayClosing(ui->closingSun->time()),
        mondayOpening(ui->openingMon->time()), mondayClosing(ui->closingMon->time()),
        tuesdayOpening(ui->openingTues->time()), tuesdayClosing(ui->closingTues->time()),
        wednesdayOpening(ui->openingWednes->time()), wednesdayClosing(ui->closingWednes->time()),
        thursdayOpening(ui->openingThurs->time()), thursdayClosing(ui->closingThurs->time()),
        fridayOpening(ui->openingFri->time()), fridayClosing(ui->closingFri->time()),
        saturdayOpening(ui->openingSatur->time()), saturdayClosing(ui->closingSatur->time());


    if (sundayOpening >= sundayClosing ||
        mondayOpening >= mondayClosing ||
        tuesdayOpening >= tuesdayClosing ||
        wednesdayOpening >= wednesdayClosing ||
        thursdayOpening >= thursdayClosing ||
        fridayOpening >= fridayClosing ||
        saturdayOpening >= saturdayClosing){
        QMessageBox::warning(this,"","The Opening Time Can't Be Greater or Equal to The Closing Time");
        return;
    }
    Library::mainLibrary().setOpeningTimes(
        ui->sunday->isChecked(), sundayOpening, sundayClosing,
        ui->monday->isChecked(), mondayOpening, mondayClosing,
        ui->tuesday->isChecked(), tuesdayOpening, tuesdayClosing,
        ui->wednesday->isChecked(), wednesdayOpening, wednesdayClosing,
        ui->thursday->isChecked(), thursdayOpening, thursdayClosing,
        ui->friday->isChecked(), fridayOpening, fridayClosing,
        ui->saturday->isChecked(), saturdayOpening, saturdayClosing);

    Helper::sendEmailToAll("Opening Schedule Changed!", "The Opening Schedule Of The Library Has Been Modified,"
                                                        "Check It On In The Application Using The About Window");

    QMessageBox::information(this,"","Success");
}


void editAboutWindow::on_addEvent_clicked()
{
    if(ui->eventitle->text().isEmpty()){
        QMessageBox::warning(this,"","The Event's Title Can't Be Empty");
        return;
    }

    string title = ui->eventitle->text().toStdString();
    if (title.size()> 50){
        QMessageBox::warning(this,"","The Event's Title Can't Exceed 50 Characters");
        return;
    }

    if (ui->eventStatringTime->dateTime() >= QDateTime :: currentDateTime()){
        QMessageBox::warning(this,"", "The Event's Opening Date & Time Can't Be Less Than The Current Date & Time");
        return;
    }

    string description = ui->eventDescription->toPlainText().toStdString();
    Time openingTime(ui->eventStatringTime->time()), closingTime(ui->eventClosingTime->time());
    Date openingDate(ui->eventStatringTime->date()), closingDate(ui->eventClosingTime->date());
    int state = Library::mainLibrary().setEvent(title,description,openingDate,openingTime,closingDate,closingTime);
    refreshTable();
    switch(state){
    case -1:
        QMessageBox::warning(this,"","Another Active Event with The Same Title");
        return;
    case -2:
        QMessageBox::warning(this,"","Opening Date & Time Must be Less Than Closing Date & Time");
        return;
    case 0:
        Helper::sendEmailToAll("New Event", "An Event Is Awaiting Your Arrival\nIts Title: " + QString::fromStdString(title) +
                               "\nIts Description: " + QString::fromStdString(description) +
                               "\nIt Starts on: " + QString::fromStdString(openingDate.toString())+ " , " +
                               QString::fromStdString(openingTime.toStringAMPM()) + "\nIt Ends on: " +
                                                QString::fromStdString(closingDate.toString())+ " , " +
                                                QString::fromStdString(closingTime.toStringAMPM()) );
        QMessageBox::information(this,"","Success");
        return;
    }
}


void editAboutWindow::on_deleteEvent_clicked()
{
    string title = ui->eventitle->text().toStdString();
    if(Library::mainLibrary().deleteEvent(title)){
        refreshTable();
        QMessageBox::information(this,"","Success");
        return;
    }
    QMessageBox :: warning(this,"","No Active Event Found With The Given Title");
}

void editAboutWindow::refreshTable(){
    if(Library::mainLibrary().libraryEvents.empty()){
        ui->events->setRowCount(1);
        ui->events->setColumnCount(1);
        QTableWidgetItem *item = new QTableWidgetItem("No Events Available");
        item->setTextAlignment(Qt::AlignCenter);
        ui->events->setItem(0, 0, item);
    }
    else{
        ui->events->setColumnCount(4);
        ui->events->setHorizontalHeaderLabels({"Event's Title", "Event's Description", "Starting Date & Time", "Ending Date & Time"});
        for (int i=0; i<Library::mainLibrary().libraryEvents.size();i++){
            string startingTime = Library::mainLibrary().libraryEvents[i].startingTime.toStringAMPM();

            QString starting = QString::fromStdString(Library::mainLibrary().libraryEvents[i].startingDate.toString() + "   "+startingTime );

            string closingTime = Library::mainLibrary().libraryEvents[i].endingTime.toStringAMPM();

            QString closing = QString::fromStdString(Library::mainLibrary().libraryEvents[i].endingDate.toString() + "   "+closingTime );

            ui->events->setItem(i,0, new QTableWidgetItem(QString :: fromStdString(Library::mainLibrary().libraryEvents[i].title)));
            ui->events->setItem(i,1, new QTableWidgetItem(QString :: fromStdString(Library::mainLibrary().libraryEvents[i].description)));
            ui->events->setItem(i,2, new QTableWidgetItem(starting));
            ui->events->setItem(i,3, new QTableWidgetItem(closing));

        }

    }
}


void editAboutWindow::on_back_clicked()
{
    this->hide();
}

