#include "windows/editwindow.h"
#include "windows/librarymanagementsystem.h"
#include "ui_editwindow.h"

editWindow::editWindow(LibraryManagementSystem* mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::editWindow), mainwindow(mainWin)
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
    ui->newTitle->setEnabled(false);
    ui->newAuthor->setEnabled(false);
    ui->newType->setEnabled(false);
    ui->newPublicationYear->setEnabled(false);
    ui->newQuantity->setEnabled(false);
    ui->newPublicationYear->setRange(-150,2300);
    ui->newQuantity->setRange(0,1000000);
    ui->oldBook->setChecked(true);
}

editWindow::~editWindow()
{
    delete ui;
}

void editWindow::on_edit_clicked()
{

        if (!(ui->oldBook->isChecked()) && !(ui->oldArticle->isChecked()) &&
            !(ui->oldDigitalContent->isChecked()) && !(ui->oldOther->isChecked()))
        {
            QMessageBox::warning(this, "Type", "A Type for The Resource You Want to Edit Must be Chosen");
            return;
        }

        pair<int,int> id;
        if (ui->oldBook->isChecked())
            id.first = 0;
        else if (ui->oldArticle->isChecked())
            id.first = 1;
        else if (ui->oldDigitalContent->isChecked())
            id.first = 2;
        else if (ui->oldOther->isChecked())
            id.first = 3;
        id.second = ui->oldId2->value();

        if (id.second >= Library::mainLibrary().libraryResources[id.first].size()) {
            QMessageBox::warning(this, "ID", "This ID Is Out Of Range");
            return;
        }

        string title, author, type;
        int quantity = 0, publicationYear = 0;
        bool changeTitle = false, changeAuthor = false, changeQuantity = false;
        bool changePublicationYear = false, changeType = false, atLeastOneEdit = false;

        if (ui->isTitle->isChecked()) {
            changeTitle = true;
            title = ui->newTitle->text().toStdString();
        }
        if (ui->isAuthor->isChecked()) {
            changeAuthor = true;
            author = ui->newAuthor->text().toStdString();
        }
        if (ui->isQuantity->isChecked()) {
            changeQuantity = true;
            quantity = ui->newQuantity->value();
        }
        if (ui->isPublicationYear->isChecked()) {
            changePublicationYear = true;
            publicationYear = ui->newPublicationYear->value();
        }
        if (ui->isType->isChecked()) {
            changeType = true;
            for (int i = 0; i < Library::mainLibrary().libraryUsers.size(); i++){
                for (int j = 0; j < Library::mainLibrary().libraryUsers[i].indexOfReservedResources.size(); j++){
                    if (Library::mainLibrary().libraryUsers[i].indexOfReservedResources[j] == id){
                        QMessageBox::warning(this, "", "Can't Edit The Type of a Reserved Resource");
                        return;
                    }
                }
            }

            for (int i = 0; i < Library::mainLibrary().libraryUsers.size(); i++){
                for (int j = 0; j < Library::mainLibrary().libraryUsers[i].borrowedResources.size(); j++){
                    if (Library::mainLibrary().libraryUsers[i].borrowedResources[j].id == id){
                        QMessageBox::warning(this, "", "Can't Edit The Type of a Borrowed Resource");
                        return;
                    }
                }
            }

            if (ui->newBook->isChecked()) {
                type = "book";
            }
            else if (ui->newDigitalContent->isChecked()) {
                type = "digital content";
            }
            else if (ui->newArticle->isChecked()) {
                type = "article";
            }
            else if (ui->newOther->isChecked()) {
                type = "other";
            }
            else {
                QMessageBox::information(this, "Type", "You Must Select a Type");
                return;
            }
        }

        atLeastOneEdit = changeTitle || changeAuthor || changeQuantity || changePublicationYear || changeType;
        if (!atLeastOneEdit) {
            QMessageBox::warning(this, "", "You Must At Least Edit One Feature");
            return;
        }

        Resource r;
        bool titleOk = true, authorOk = true, yearOk = true;

        if (changeTitle) {
            titleOk = r.setTitle(title);
            if (!titleOk) {
                QMessageBox::warning(this, "Title", Library::errors[0]);
                return;
            }
        }
        if (changeAuthor) {
            authorOk = r.setAuthor(author);
            if (!authorOk) {
                QMessageBox::warning(this, "Author", Library::errors[1]);
                return;
            }
        }
        if (changePublicationYear) {
            yearOk = r.setPublicationYear(publicationYear);
            if (!yearOk) {
                QMessageBox::warning(this, "Publication Year", Library::errors[2]);
                return;
            }
        }

        if (changeQuantity) {
            r.setQuantity(quantity);
        }
        if (changeType) {
            r.setType(type);
        }

        Library::mainLibrary().editResource(id, r, changeTitle, changeAuthor, changeQuantity, changePublicationYear, changeType);
        int newRow = Helper :: setRowIndex(type);
        string message = "The Resource Has Been Edited Successfully\nResource's Information:\nType: "
                         + Library::mainLibrary().libraryResources[newRow].back().getType() +
                         "\nTitle: " + Library::mainLibrary().libraryResources[newRow].back().getTitle() +
                         "\nIdentifier: (" + to_string(newRow) + "," + to_string(Library::mainLibrary().libraryResources[newRow].back().id.second) + ")" +
                         "\nAuthor: " + Library::mainLibrary().libraryResources[newRow].back().getAuthor() +
                         "\nPublication Year: " + to_string(Library::mainLibrary().libraryResources[newRow].back().getPublicationYear()) +
                         "\nQuantity: " + to_string(Library::mainLibrary().libraryResources[newRow].back().getQuantity());

    QMessageBox::information(this, "Success", QString::fromStdString(message));
    on_reset_clicked();

}



void editWindow::on_isAuthor_stateChanged(int state)
{
    if (state == Qt :: Checked) {
        ui->newAuthor->setEnabled(true);
        string type;
        if (ui->oldBook->isChecked()) type = "book";
        else if (ui->oldArticle->isChecked()) type = "article";
        else if (ui->oldDigitalContent->isChecked()) type = "digital content";
        else if (ui->oldOther->isChecked()) type = "other";
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->oldId2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r != Resource("out of range", "out of range", 0))
        ui->newAuthor->setText(QString :: fromStdString(r.getAuthor()));
    }

    else{
        ui->newAuthor->setEnabled(false);
    }
}


void editWindow::on_isTitle_stateChanged(int state)
{
    if (state == Qt :: Checked) {
        ui->newTitle->setEnabled(true);
        string type;
        if (ui->oldBook->isChecked()) type = "book";
        else if (ui->oldArticle->isChecked()) type = "article";
        else if (ui->oldDigitalContent->isChecked()) type = "digital content";
        else if (ui->oldOther->isChecked()) type = "other";
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->oldId2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r != Resource("out of range", "out of range", 0))
            ui->newTitle->setText(QString :: fromStdString(r.getTitle()));
    }

    else{
        ui->newTitle->setEnabled(false);
    }
}


void editWindow::on_isQuantity_stateChanged(int state)
{
    if (state == Qt :: Checked) {
        ui->newQuantity->setEnabled(true);
        string type;
        if (ui->oldBook->isChecked()) type = "book";
        else if (ui->oldArticle->isChecked()) type = "article";
        else if (ui->oldDigitalContent->isChecked()) type = "digital content";
        else if (ui->oldOther->isChecked()) type = "other";
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->oldId2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r != Resource("out of range", "out of range", 0))
            ui->newQuantity->setValue(r.getQuantity());
    }

    else{
        ui->newQuantity->setEnabled(false);
    }
}


void editWindow::on_isType_stateChanged(int state)
{
    if (state == Qt :: Checked) {
        ui->newType->setEnabled(true);
        ui->newBook->setEnabled(true);
    }

    else{
        ui->newType->setEnabled(false);
    }
}


void editWindow::on_isPublicationYear_stateChanged(int state)
{
    if (state == Qt :: Checked) {
        ui->newPublicationYear->setEnabled(true);
        string type;
        if (ui->oldBook->isChecked()) type = "book";
        else if (ui->oldArticle->isChecked()) type = "article";
        else if (ui->oldDigitalContent->isChecked()) type = "digital content";
        else if (ui->oldOther->isChecked()) type = "other";
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->oldId2->value());
        Resource r = Library::mainLibrary().findResource(id);
        if (r != Resource("out of range", "out of range", 0))
            ui->newPublicationYear->setValue(r.getPublicationYear());
    }

    else{
        ui->newPublicationYear->setEnabled(false);
    }
}


void editWindow::on_reset_clicked()
{
    ui->newPublicationYear->clear();
    ui->newAuthor->clear();
    ui->newTitle->clear();
    ui->newQuantity->clear();
    ui->newBook->setChecked(false);
    ui->newArticle->setChecked(false);
    ui->newDigitalContent->setChecked(false);
    ui->newOther->setChecked(false);
    ui->newType->setChecked(false);
}


void editWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}

