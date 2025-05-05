#include "windows/removewindow.h"
#include "ui_removewindow.h"
#include "windows/librarymanagementsystem.h"
#include <QMessageBox>

removeWindow::removeWindow(LibraryManagementSystem* mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::removeWindow), mainwindow(mainWin)
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
    ui->id2->setRange(0,10000);
}

removeWindow::~removeWindow()
{
    delete ui;
}

void removeWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void removeWindow::on_remove_clicked()
{
    if(!ui->book->isChecked() && !ui->article->isChecked() && !ui->digitalcontent->isChecked() && !ui->other->isChecked()){
        QMessageBox :: warning (this,"Warning","You Must Enter The Resource's Type");
        return;
    }

    pair<int,int> id;
    if (ui->book->isChecked())
        id.first = 0;
    else if (ui->article->isChecked())
        id.first=1;
    else if (ui->digitalcontent->isChecked())
        id.first =2;
    else if (ui->other->isChecked())
        id.first=3;
    id.second = ui->id2->value();
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        for (int j =0; j < Library::mainLibrary().libraryUsers[j].indexOfReservedResources.size(); j++){
            if(Library::mainLibrary().libraryUsers[j].indexOfReservedResources[j]==id){
                QMessageBox :: warning(this,"","Can't Remove a Reserved Resource");
                return;
            }
        }
    }
    for (int i =0; i < Library::mainLibrary().libraryUsers.size(); i++){
        for (int j =0; j < Library::mainLibrary().libraryUsers[j].borrowedResources.size(); j++){
            if(Library::mainLibrary().libraryUsers[j].borrowedResources[j].id==id){
                QMessageBox :: warning(this,"","Can't Remove a Borrowed Resource");
                return;
            }
        }
    }
    int result = Library :: mainLibrary().removeResource(id);
    if(result == -2) {
        QMessageBox :: warning(this,"Borrowed Item", "This Item is Borrowed by Someone\nIt Can't be Removed");
        return;
    }
    if (result == -1){
        QMessageBox :: warning (this,"ID","The Given ID is Out of Range");
        return;
    }

    if (result == 0){
        QMessageBox :: information (this,"Success", "The Resource Has Been Removed Successfully");
    }

}


void removeWindow::on_clear_clicked()
{
    if (Helper::confirmAction(this)){
        for (int i =0;i<4;i++){
            if (Library::mainLibrary().libraryResources[i].empty()) continue;
            Library::mainLibrary().libraryResources[i].clear();
        }
    }
}

