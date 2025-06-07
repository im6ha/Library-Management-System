#include "windows/emailwindow.h"
#include "ui_emailwindow.h"
#include "windows/librarymanagementsystem.h"
#include <QMessageBox>

emailwindow::emailwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::emailwindow)
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
    printEmails();
}

emailwindow::~emailwindow()
{
    delete ui;
}

void emailwindow :: printEmails(){
    ui->emails->setRowCount(0);
    ui->emails->setColumnCount(1);
    ui->emails->setHorizontalHeaderLabels({"Email"});
    ui->emails->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    if (Library::mainLibrary().libraryEmails.empty()) return;
    for (Email email : Library::mainLibrary().libraryEmails){
        int row = ui->emails->rowCount();
        ui->emails->insertRow(row);

        ui->emails->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(email.getEmail())));
    }
}

void emailwindow::on_add_clicked()
{
    if(ui->email->text().isEmpty()){
        QMessageBox:: warning(this,"","Please enter an email");
        return;
    }
    string email = ui->email->text().toStdString();
    if(!Email::checkEmail(email)){
        QMessageBox :: warning(this,"","The enterred email is in wrong format");
        return;
    }
    for (int i=0; i < Library::mainLibrary().libraryEmails.size();i++){
        if (Library::mainLibrary().libraryEmails[i].getEmail() == email){
            QMessageBox :: warning(this,"","The email was already found");
            return;
        }
    }
    Library::mainLibrary().libraryEmails.push_back(Email(email));
    QMessageBox::information(this,"",QString::fromStdString(email) + " was successfully added");
    printEmails();
}


void emailwindow::on_delete_2_clicked()
{
    int found = -1;
    if(ui->email->text().isEmpty()){
        QMessageBox:: warning(this,"","Please enter an email");
        return;
    }
    string email = ui->email->text().toStdString();
    if(!Email::checkEmail(email)){
        QMessageBox :: warning(this,"","The enterred email is in wrong format");
        return;
    }

    for (int i=0; i < Library::mainLibrary().libraryEmails.size();i++){
        if (Library::mainLibrary().libraryEmails[i].getEmail() == email){
            found = i;
            break;
        }
    }
        if (found == -1) {
        QMessageBox:: warning(this,"","The entered email doesn't match a library email");
            return;
        }

        Library::mainLibrary().libraryEmails.erase(Library::mainLibrary().libraryEmails.begin() + found);
        QMessageBox::information(this,"",QString::fromStdString(email) + " was successfully deleted");
        printEmails();
}




void emailwindow::on_send_clicked()
{
    if(ui->sendEmail->toPlainText().isEmpty()) {
        QMessageBox:: warning(this,"","Please don't leave the body empty");
        return;
    }
    if(Library::mainLibrary().libraryEmails.empty()){
        QMessageBox :: warning(this,"","There is no library email to send the email to");
        return;
    }

    QString body = ui->sendEmail->toPlainText();
    QString subject = ui->subject->text();

    Helper::sendEmailToAll(subject,body);
    QMessageBox::information(this,"","The email was successfully sent");
}


void emailwindow::on_back_clicked()
{
    this->hide();
    mainWindow->show();
}

