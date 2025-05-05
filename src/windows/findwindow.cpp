#include "windows/findwindow.h"
#include "ui_findwindow.h"
#include "windows/librarymanagementsystem.h"
#include <QDebug>


findWindow::findWindow(LibraryManagementSystem* mainWin, QWidget *parent)
    : QDialog(parent), ui(new Ui::findWindow), mainwindow(mainWin)
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
    ui->resultTable->setColumnCount(8);
    ui->resultTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Author", "Pub. Year",
                                                "Quantity", "Borrowed", "#Reservations"});


    print2DLibrary();

    ui->inputPublicationYear->setRange(0,10000);
    ui->inputAuthor->setEnabled(false);
    ui->inputPublicationYear->setEnabled(false);
    ui->inputTitle->setEnabled(false);
    ui->id2->setEnabled(false);
    ui->type->setEnabled(false);
    ui->showFullAuthor->setEnabled(false);
    ui->showFullTitle->setEnabled(false);

    ui->unsort->setChecked(true);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

findWindow::~findWindow()
{
    delete ui;
}

void findWindow :: print2DLibrary(){
    for (int i =0; i <4; i++){
        if (Library::mainLibrary().libraryResources[i].empty()) continue;
        for (int j=0; j<Library::mainLibrary().libraryResources[i].size(); j++){
            Resource current_resource = Library::mainLibrary().libraryResources[i][j];
            char isBorrowed = (current_resource.isBorrowed)? 'Y' : 'n';
            QString id = "("+QString :: number(Library::mainLibrary().findResource(current_resource).first)+
                         "," + QString :: number(Library::mainLibrary().findResource(current_resource).second)+
                         ")";
            addRow(id,QString::fromStdString(current_resource.getType()) ,
                   QString :: fromStdString(current_resource.getTitle()),
                   QString :: fromStdString(current_resource.getAuthor()),
                   current_resource.getPublicationYear(),
                   current_resource.getQuantity(), isBorrowed, current_resource.getReservations());
        }
    }

}

void findWindow :: print1DLibrary(vector<Resource> sorted){
    for (int j=0; j<sorted.size(); j++){
        Resource current_resource = sorted[j];
        char isBorrowed = (current_resource.isBorrowed)? 'Y' : 'n';
        QString id = "("+QString :: number(current_resource.id.first)+
                     "," + QString :: number(current_resource.id.second)+
                     ")";
        addRow(id,QString::fromStdString(current_resource.getType()) ,
               QString :: fromStdString(current_resource.getTitle()),
               QString :: fromStdString(current_resource.getAuthor()),
               current_resource.getPublicationYear(),
               current_resource.getQuantity(), isBorrowed, current_resource.getReservations());
    }
}

void findWindow::addRow(QString id, QString type, QString title, QString author,
                        int publicationYear, int quantity, char borrowed, int numberOfReservations) {
    int row = ui->resultTable->rowCount();
    ui->resultTable->insertRow(row);

    ui->resultTable->setItem(row, 0, new QTableWidgetItem(id));
    ui->resultTable->setItem(row, 1, new QTableWidgetItem(type));
    ui->resultTable->setItem(row, 2, new QTableWidgetItem(title));
    ui->resultTable->setItem(row, 3, new QTableWidgetItem(author));
    ui->resultTable->setItem(row, 4, new QTableWidgetItem(QString::number(publicationYear)));
    ui->resultTable->setItem(row, 5, new QTableWidgetItem(QString::number(quantity)));
    ui->resultTable->setItem(row, 6, new QTableWidgetItem(QString(borrowed)));
    ui->resultTable->setItem(row, 7, new QTableWidgetItem(QString::number(numberOfReservations)));
}

void findWindow::reverseTable(QTableWidget* table) {
    int rowCount = table->rowCount();
    int columnCount = table->columnCount();

    for (int i = 0; i < rowCount / 2; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            QTableWidgetItem* item1 = table->takeItem(i, j);
            QTableWidgetItem* item2 = table->takeItem(rowCount - i - 1, j);

            table->setItem(i, j, item2);
            table->setItem(rowCount - i - 1, j, item1);
        }
    }
}

void findWindow::on_isPublication_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->inputPublicationYear->setEnabled(true);
        ui->isID2->setChecked(false);
    }
    else if (state == Qt::Unchecked){
        ui->inputPublicationYear->setEnabled(false);
    }

    if (ui->isTitle->isChecked() && ui->isPublication->isChecked() && ui->isAuthor->isChecked() &&
        ui->isID1->isChecked()){
        ui->isResource->setChecked(true);
    }
    else {
        ui->isResource->setChecked(false);
    }

}


void findWindow::on_isAuthor_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->inputAuthor->setEnabled(true);
        ui->isID2->setChecked(false);
        ui->showFullAuthor->setEnabled(true);
    }

    else if (state == Qt::Unchecked){
        ui->inputAuthor->setEnabled(false);
        ui->showFullAuthor->setChecked(false);
        ui->showFullAuthor->setEnabled(false);

    }

    if (ui->isTitle->isChecked() && ui->isPublication->isChecked() && ui->isAuthor->isChecked() &&
        ui->isID1->isChecked()){
        ui->isResource->setChecked(true);
    }
    else {
        ui->isResource->setChecked(false);
    }
}

void findWindow::on_isTitle_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->inputTitle->setEnabled(true);
        ui->isID2->setChecked(false);
        ui->showFullTitle->setEnabled(true);
    }
    else if (state == Qt::Unchecked){
        ui->inputTitle->setEnabled(false);
        ui->showFullTitle->setChecked(false);
        ui->showFullTitle->setEnabled(false);
    }

    if (ui->isTitle->isChecked() && ui->isPublication->isChecked() && ui->isAuthor->isChecked() &&
        ui->isID1->isChecked()){
        ui->isResource->setChecked(true);
    }
    else {
        ui->isResource->setChecked(false);
    }
}


void findWindow::on_isResource_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->isAuthor->setChecked(true);
        ui->isAuthor->setEnabled(false);
        ui->isTitle->setChecked(true);
        ui->isTitle->setEnabled(false);
        ui->isPublication->setChecked(true);
        ui->isPublication->setEnabled(false);
        ui->isID1->setChecked(true);
        ui->isID1->setEnabled(false);
        return;
    }

    if (state == Qt::Unchecked){
        ui->isAuthor->setEnabled(true);
        ui->isTitle->setEnabled(true);
        ui->isPublication->setEnabled(true);
        ui->isID1->setEnabled(true);
    }
}




void findWindow::on_isID1_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->type->setEnabled(true);
    }
    else if (state == Qt::Unchecked) {
        ui->type->setEnabled(false);
        ui->isID2->setChecked(false);
        ui->isID2->setEnabled(false);
    }


    if (ui->isTitle->isChecked() && ui->isPublication->isChecked() && ui->isAuthor->isChecked() &&
        ui->isID1->isChecked()){
        ui->isResource->setChecked(true);
    }
    else {
        ui->isResource->setChecked(false);
    }
}


void findWindow::on_isID2_stateChanged(int state)
{
    ui->resultTable->setRowCount(0);

    if (state == Qt :: Checked){
        ui->id2->setEnabled(true);
        ui->isID1->setChecked(true);
        ui->isID1->setEnabled(false);
        ui->isAuthor->setChecked(false);
        ui->isAuthor->setEnabled(false);
        ui->isTitle->setChecked(false);
        ui->isTitle->setEnabled(false);
        ui->isPublication->setChecked(false);
        ui->isPublication->setEnabled(false);
        ui->isResource->setChecked(false);
        ui->isResource->setEnabled(false);
        return;
    }

    if (state == Qt :: Unchecked){
        ui->id2->setEnabled(false);
        ui->isID1->setEnabled(true);
        ui->isAuthor->setEnabled(true);
        ui->isResource->setEnabled(true);
        ui->isTitle->setEnabled(true);
        ui->isPublication->setEnabled(true);
    }
}


void findWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void findWindow::on_find_clicked()
{
    bool empty = true;
    for (int i =0;i<4;i++){
        if(!Library::mainLibrary().libraryResources[i].empty()){
            empty=false;
            break;
        }
    }
    if (empty){
        QMessageBox::warning(this,"","The Library Is Empty");
        return;
    }

    if (!ui->isTitle->isChecked() && !ui->isAuthor->isChecked() && !ui->isID1->isChecked() &&
        !ui->isPublication->isChecked()){
        QMessageBox :: warning (this,"","At Least One Field Must Be Chosen");
        return;
    }
    ui->resultTable->setRowCount(0);


    string title,type,author;
    int publicationYear = 0;
    pair<int,int> id;
    Resource r;

    if (!ui->isID2->isChecked() && !ui->isResource->isChecked()){
    vector <pair<int,int>> v1,v2,v3,v4,result;
    v1=v2=v3=v4 = {make_pair(-2,-2)};


    if (ui->isTitle->isChecked() && ui->showFullTitle->isChecked()){
        title = (ui->inputTitle->text()).toStdString();
        v1 = Library :: mainLibrary().findResourceTitle(title);
    }

    if (ui->isTitle->isChecked() && !ui->showFullTitle->isChecked()){
        title = (ui->inputTitle->text()).toStdString();
        v1 = Library :: mainLibrary().findResourceKeyword(title);
    }

    if (ui->isAuthor->isChecked() && ui->showFullAuthor->isChecked()){
        author = (ui->inputAuthor->text()).toStdString();
        v2 = Library :: mainLibrary().findResourceAuthor(author);
    }

    if (ui->isAuthor->isChecked() && !ui->showFullAuthor->isChecked()){
        author = (ui->inputAuthor->text()).toStdString();
        v2 = Library :: mainLibrary().findResourceKeywordAuthor(author);
    }

    if (ui->isPublication->isChecked()){
        publicationYear = ui->inputPublicationYear->value();
        v3 = Library :: mainLibrary().findResourcePublication(publicationYear);
    }

    if (ui->isID1->isChecked()){
        if (ui->book->isChecked()){
            type = "book";
        }
        if(ui->article->isChecked()){
            type = "article";
        }
        if(ui->digitalcontent->isChecked()){
            type = "digital content";
        }
        if(ui->other->isChecked()){
            type = "other";
        }
        v4 = Library :: mainLibrary().findResourceType(type);
    }
        result = Helper :: intersection(v1,v2,v3,v4);
    if (result.size() == 1 && result[0] == make_pair(-1,-1)){
            QMessageBox :: warning (this, "", "No Matching Results");
            return;
    }
    if (!result.empty()) {
        for (pair<int,int> idPair : result) {
            if (idPair == make_pair(-1,-1)) continue;
            Resource current_resource = Library::mainLibrary().findResource(idPair);
            char isBorrowed = current_resource.isBorrowed ? 'Y' : 'n';
            QString id = "(" + QString::number(idPair.first) + "," + QString::number(idPair.second) + ")";
            addRow(id, QString::fromStdString(current_resource.getType()),
                   QString::fromStdString(current_resource.getTitle()),
                   QString::fromStdString(current_resource.getAuthor()),
                   current_resource.getPublicationYear(),
                   current_resource.getQuantity(), isBorrowed, current_resource.getReservations());
        }
    } else {
        QMessageBox::warning(this, "", "No Matching Results");
    }    }
    else {
        if (ui->isID2->isChecked()) {
            if (ui->book->isChecked()) type = "book";
            else if (ui->article->isChecked()) type = "article";
            else if (ui->digitalcontent->isChecked()) type = "digital content";
            else if (ui->other->isChecked()) type = "other";
            else {
                QMessageBox::warning(this, "", "Select a resource type for ID2.");
                return;
            }
            id = make_pair(Helper::setRowIndex(type), ui->id2->value());
        }

        if (ui->isResource->isChecked()) {
            r.setAll(title, author, publicationYear, 0, type);
            id = Library::mainLibrary().findResource(r);
        }

        if (id == make_pair(-1, -1)) {
            QMessageBox::warning(this, "", "No Matching Results");
            return;
        }

        if (id.first >= 4 || id.second >= Library::mainLibrary().libraryResources[id.first].size()) {
            QMessageBox::warning(this, "", "ID Out of Range");
            return;
        }

        Resource current_resource = Library::mainLibrary().findResource(id);
        if (current_resource.getTitle() == "out of range") {
            QMessageBox::warning(this, "", "Resource not found.");
            return;
        }

        char isBorrowed = current_resource.isBorrowed ? 'Y' : 'n';
        QString Qid = "(" + QString::number(id.first) + "," + QString::number(id.second) + ")";
        addRow(Qid, QString::fromStdString(current_resource.getType()),
               QString::fromStdString(current_resource.getTitle()),
               QString::fromStdString(current_resource.getAuthor()),
               current_resource.getPublicationYear(),
               current_resource.getQuantity(), isBorrowed, current_resource.getReservations());
    }

}

//sorting/filtering


void findWindow::on_unsort_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    print2DLibrary();
}


void findWindow::on_author_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    Library::mainLibrary().sortAuthor();
    vector<Resource> sorted = Library::mainLibrary().oneD_libraryResources;

    if (ui->reverseOrder->isChecked()) {
        Helper::reverse(sorted);
    }

    print1DLibrary(sorted);
}


void findWindow::on_publicationYear_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    Library::mainLibrary().sortPublicationYear();
    vector<Resource>sorted = Library::mainLibrary().oneD_libraryResources;

    if (ui->reverseOrder->isChecked()){
        Helper :: reverse(sorted);
    }
    print1DLibrary(sorted);
}


void findWindow::on_quantity_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    vector<Resource> sorted;
    Library::mainLibrary().sortQuantity();
    sorted = Library::mainLibrary().oneD_libraryResources;

    if (ui->reverseOrder->isChecked()){
        Helper :: reverse(sorted);
    }

    print1DLibrary(sorted);
}


void findWindow::on_reservation_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    vector<Resource> sorted;
    Library::mainLibrary().sortNumberOfReservations();
    sorted = Library::mainLibrary().oneD_libraryResources;

    if (ui->reverseOrder->isChecked()){
        Helper ::  reverse(sorted);
    }


    print1DLibrary(sorted);
}


void findWindow::on_title_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    vector<Resource> sorted;
    Library::mainLibrary().sortTitle();
    sorted = Library::mainLibrary().oneD_libraryResources;

    if (ui->reverseOrder->isChecked()){
        Helper :: reverse(sorted);
    }

    print1DLibrary(sorted);
}


void findWindow::on_availability_clicked(bool)
{
    ui->resultTable->setRowCount(0);
    vector<Resource> sorted = Library::mainLibrary().availabileResources();
    if (ui->reverseOrder->isChecked())
        Helper::reverse(sorted);

    print1DLibrary(sorted);
}





void findWindow::on_reverseOrder_clicked(bool)
{
    reverseTable(ui->resultTable);
}


