#include "windows/addwindow.h"
#include "windows/librarymanagementsystem.h"
#include "qdatetime.h"
#include "ui_addwindow.h"

addWindow::addWindow(LibraryManagementSystem* mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::addWindow), mainwindow(mainWin)
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
    ui->inputPublicationYear->setValue(QDate::currentDate().year());
    ui->inputQuantity->setValue(0);
    ui->inputPublicationYear->setRange(0,2500);
    ui->inputQuantity->setRange(0,100000);
    ui->inputPublicationYear->setValue(QDate::currentDate().year());
    ui->book->setChecked(true);
}

addWindow::~addWindow()
{
    delete ui;
}



void addWindow::on_add_clicked() //"unknow" is the default argument for author
{

    if (ui->inputTitle->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "", "The Title Field Must be Full");
        return;
    }

    string title, author, type;
    int quantity, publicationYear;
    if (ui->inputAuthor->text().trimmed().isEmpty()){
        ui->inputAuthor->setText("Unknown");
    }

    title = (ui->inputTitle->text()).toStdString();
    quantity = ui->inputQuantity->value();
    author = (ui->inputAuthor->text()).toStdString();
    publicationYear = ui ->inputPublicationYear->value();
    if (ui->book->isChecked()) {
        type = "book";
    }

    else if (ui->digitalcontent->isChecked()) {
        type = "digital content";
    }

    else if (ui->article->isChecked()) {
        type = "article";
    }

    else if (ui->other->isChecked()) {
        type = "other";
    }
    else{
        QMessageBox::information(this, "Type", "You Must Select a Type");
        return;
    }


    Resource r;
    bool checks[] = {r.setTitle(title), r.setAuthor(author),r.setPublicationYear(publicationYear)};
    if (!checks[0] && checks[1] && checks[2]) {
        QMessageBox::warning(this, "Title", Library::errors[0]);
        return;
    }
    else if (!checks[1] && checks[0] && checks[2]) {
        QMessageBox::warning(this, "Author", Library::errors[1]);
        return;
    }
    else if (!checks[2] && checks[0] && checks[1]) {
        QMessageBox::warning(this, "Publication Year", Library::errors[2]);
        return;
    }
    else if (!checks[0] && !checks[1] && checks[2]) {
        QMessageBox::warning(this, "Title & Author", Library::errors[0] + "\n" + Library::errors[1]);
        return;
    }
    else if (!checks[0] && !checks[2] && checks[1]) {
        QMessageBox::warning(this, "Title & Publication Year", Library::errors[0] + "\n" + Library::errors[2]);
        return;
    }
    else if (!checks[1] && !checks[2] && checks[0]) {
        QMessageBox::warning(this, "Author & Publication Year", Library::errors[1] + "\n" + Library::errors[2]);
        return;
    }
    else if (!checks[0] && !checks[1] && !checks[2]) {
        QMessageBox::warning(this, "Title, Author & Publication Year", Library::errors[0] + "\n" + Library::errors[1] + "\n" + Library::errors[2]);
        return;
    }
    else if (checks[0] && checks[1] && checks[2]){
        r.setQuantity(quantity);
        r.setType(type);
        on_reset_clicked();

        string message;
        pair <int,int> index = Library :: mainLibrary().addResource(r);
        int newRow = Helper :: setRowIndex(type);
        if (index == make_pair(-1,-1)){
            string resourceDetails = "\nResource's Information:\nType: " +
                                     Library :: mainLibrary().libraryResources[newRow].back().getType() +
                                     "\nTitle: " + Library :: mainLibrary().libraryResources[newRow].back().getTitle()
                                     +"\nIdentifier: (" + to_string(newRow)+","
                                     + to_string(Library :: mainLibrary().libraryResources[newRow].back().id.second)
                                     +")"
                                     +"\nAuthor: " + Library :: mainLibrary().libraryResources[newRow].back().getAuthor()
                                     + "\nPublication Year: " + to_string(Library :: mainLibrary().libraryResources[newRow].back().getPublicationYear())
                                     + "\nQuantity: " + to_string(Library :: mainLibrary().libraryResources[newRow].back().getQuantity());
            message = "Resource Added Successfullt!\n" + resourceDetails;
            Helper::sendEmailToAll("New Resource!!!!",
                                   "A New Resource Has Been Added To The Library\n" +
                                    QString::fromStdString(resourceDetails));
        }
        else {
            if (r.getQuantity()==0) {
                message = "Resource Already Exists \nIdentifier: ("
                          + to_string(r.id.first)+","
                          + to_string(r.id.second)
                          +")";
            }
            else{
                 message ="Resource Already Exists\nIncrementing Its Quantity\nResources Information:\nType:"
                      + Library::mainLibrary().libraryResources[index.first][index.second].getType()
                      +"\nIdentifier: (" + to_string(r.id.first)+","
                      + to_string(r.id.second)
                      +")"
                      +"\nAuthor: "
                      + Library::mainLibrary().libraryResources[index.first][index.second].getAuthor()
                      +"\nPublication Year: "
                      + to_string(Library::mainLibrary().libraryResources[index.first][index.second].getPublicationYear())
                      + "\nQuantity: "
                      + to_string(Library::mainLibrary().libraryResources[index.first][index.second].getQuantity());

            }}
            QString Qmessage = QString::fromStdString(message);


        QMessageBox::information(this, "Success",Qmessage);
    }

}


void addWindow::on_reset_clicked()
{
    ui->inputPublicationYear->clear();
    ui->inputAuthor->clear();
    ui->inputTitle->clear();
    ui->inputQuantity->clear();
    ui->book->setAutoExclusive(false);
    ui->article->setAutoExclusive(false);
    ui->digitalcontent->setAutoExclusive(false);
    ui->other->setAutoExclusive(false);
    ui->book->setChecked(false);
    ui->article->setChecked(false);
    ui->digitalcontent->setChecked(false);
    ui->other->setChecked(false);
    ui->book->setAutoExclusive(true);
    ui->article->setAutoExclusive(true);
    ui->digitalcontent->setAutoExclusive(true);
    ui->other->setAutoExclusive(true);

}




void addWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


