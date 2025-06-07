#include "windows/reservewindow.h"
#include "ui_reservewindow.h"
#include <QMessageBox>
#include "library.h"
#include "QInputDialog"
#include "windows/addwindow.h"
#include <QMessageBox>
#include "windows/librarymanagementsystem.h"


reserveWindow::reserveWindow(LibraryManagementSystem* mainWin, User* loggedInUser, QWidget *parent)
    : QDialog(parent), ui(new Ui::reserveWindow), mainwindow(mainWin)

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
    history = nullptr;
    ui->isID->setChecked(true);
    ui->inputPublicationYear->setMaximum(3000);
    ui->isUsername->setChecked(true);
    if (loggedInUser) {
        currentUser = new User(*loggedInUser);
    } else {
        currentUser = nullptr;
    }
    if(currentUser && !currentUser->getAdmin()){
        ui->currentUser->setChecked(true);
    }

    if (currentUser && currentUser->getAdmin()){
        ui->password->setEnabled(false);
    }
}

reserveWindow::~reserveWindow()
{
    delete currentUser;
    delete ui;
}


void reserveWindow::on_currentUser_stateChanged(int state)
{
    if(state == Qt::Checked){
        if (currentUser->getAdmin()){
            ui->currentUser->setChecked(false);
            QMessageBox :: warning (this,"","Can't Reserve Resources as Admin User");
            return;
        }
        ui->userInfo->setEnabled(false);
        ui->isID->setChecked(true);
    }

    else{
        ui->userInfo->setEnabled(true);
        ui->isId->setChecked(true);
    }
}


void reserveWindow::on_isId_clicked()
{
    ui->username->text().clear();
    ui->username->setEnabled(false);
    ui->isUsername->setChecked(false);
    ui->id->setEnabled(true);
}


void reserveWindow::on_isUsername_clicked()
{
    ui->id->setEnabled(false);
    ui->username->setEnabled(true);
    ui->isId->setChecked(false);
}


void reserveWindow::on_find_clicked()
{
    User* u;
    if (ui->currentUser->isChecked()){
        u = currentUser;
    }
    else{
        int findUser;
        if (ui->isId->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->id->value());
        }
        else{
            findUser = Library::mainLibrary().findUser(ui->username->text().toStdString());
        }

        if (findUser == -1){
            QMessageBox :: warning(this,"","Given ID doesn't match an existing user");
            return;
        }
        if(Library::mainLibrary().libraryUsers[findUser].getAdmin()){
            QMessageBox :: warning(this,"","Can't Reserve a Resource as An Admin");
            return;
        }
        if(currentUser->getAdmin() || Library::mainLibrary().libraryUsers[findUser].getPassword()==ui->password->text().toStdString()){
            u = &Library::mainLibrary().libraryUsers[findUser];
        }
        else if (Library::mainLibrary().libraryUsers[findUser].getPassword()!=ui->password->text().toStdString()){
            QMessageBox :: warning(this,"warning","Enterred Password is Wrong");
        }
    }
    if (!ui->book->isChecked()&&!ui->article->isChecked() && !ui->digitalcontent->isChecked()&&
        !ui->other->isChecked()){
        QMessageBox :: warning (this,"","The Resource's Type Must Be Provided");
        return;
    }

    if (ui->isResource->isChecked() && (ui->inputAuthor->text().isEmpty() || ui->inputTitle->text().isEmpty())){
        QMessageBox :: warning (this,"","All Resource's Related Information Must Be Provided");
        return;
    }

    string type;
    if (ui->book->isChecked()){
        type ="Book";
    }
    else if(ui->article->isChecked()){
        type = "Article";
    }
    else if(ui->digitalcontent->isChecked()){
        type ="digital content";
    }
    else {
        type = "other";
    }
    if (ui->isID->isChecked()){
        Resource r = Library::mainLibrary().findResource(make_pair(Helper :: setRowIndex(type), ui->id2->value()));
        if(r == Resource("out of range", "out of range", 0)){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Add Resource", "The Enterred Resource Doesn't Exist in The Current Library\n"
                                                                "Do You Want To Add it",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                    QMessageBox :: warning(this,"","To Add a New Resource, You Must Enter The Resource's Information"
                                                       "By Checking the By Resource Box");
                    return;
            } else {
                QMessageBox::information(this, "Cancelled", "You chose No.");
                return;
            }
        }
        else{
            Library::mainLibrary().reserveResource(*u,
                                            Library::mainLibrary().libraryResources[Helper :: setRowIndex(type)][ui->id2->value()]);
            QMessageBox::information(this,"Success","Resource Reserrved Successfully");
        }

    }
    else if (ui->isResource->isChecked()){
        pair<int,int> id = Library::mainLibrary().findResource(Resource(ui->inputTitle->text().toStdString(),
                                                                         ui->inputAuthor->text().toStdString(),
                                                                         ui->inputPublicationYear->value(),
                                                                         0,type));
        if (id == make_pair(-1,-1)){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Add Resource", "The Enterred Resource Doesn't Exist in The Current Library\n"
                                                                "Do You Want To Add it",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                QString username ,pass;
                if (!currentUser->getAdmin()){
                   username = QInputDialog::getText(this, "Logged-in As Regular User", "Enter An Admin's Account Information\nUsername:");
                    pass = QInputDialog::getText(this, "Logged-in As Regular User", "Enter An Admin's Account Informatio\nPassword:");}
                else {
                    QMessageBox::information(this,"","No Need to Enter Admin's Account Information Since The Current Logged-in User is Already an Admin");
                    username = QString::fromStdString(currentUser->getUsername());
                    pass = QString::fromStdString(currentUser->getPassword());
                }
                if(Library::mainLibrary().login(username.toStdString(), pass.toStdString()).first == 1 || currentUser->getAdmin()){
                    string title, author;
                    int publicationYear;
                    title = (ui->inputTitle->text()).toStdString();
                    author = (ui->inputAuthor->text()).toStdString();
                    publicationYear = ui ->inputPublicationYear->value();

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
                        r.setType(type);
                        r.setQuantity(0);

                        string message;
                        Library :: mainLibrary().addResource(r);
                        int newRow = Helper :: setRowIndex(type);
                            message = "Resource Added and Reserved Successfullt!\n\nResource's Information:\nType: "
                                      + Library :: mainLibrary().libraryResources[newRow].back().getType() +
                                      "\nTitle: " + Library :: mainLibrary().libraryResources[newRow].back().getTitle()
                                      +"\nIdentifier: (" + to_string(newRow)+","
                                      + to_string(Library :: mainLibrary().libraryResources[newRow].back().id.second)
                                      +")"
                                      +"\nAuthor: " + Library :: mainLibrary().libraryResources[newRow].back().getAuthor()
                                      + "\nPublication Year: " + to_string(Library :: mainLibrary().libraryResources[newRow].back().getPublicationYear())
                                      + "\nQuantity: " + to_string(Library :: mainLibrary().libraryResources[newRow].back().getQuantity())
                                      + "\nReservations: 1";
                            Library ::mainLibrary().reserveResource(*u,r);
                            QString Qmessage = QString::fromStdString(message);
                            QMessageBox::information(this, "Success",Qmessage);
                        }

                    }
                } else {
                QMessageBox::information(this, "Cancelled", "You chose No.");
                return;
                 }

        }else{
            Library::mainLibrary().reserveResource(*u,
                                                   Library::mainLibrary().libraryResources[id.first][id.second]);
            QMessageBox::information(this,"Success","Resource Reserrved Successfully");
        }
    }
}


void reserveWindow::on_isResource_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->id2->setEnabled(false);
        ui->isID->setChecked(false);
        ui->type->setEnabled(true);
        ui->inputAuthor->setEnabled(true);
        ui->inputPublicationYear->setEnabled(true);
        ui->inputTitle->setEnabled(true);
    }
    else{
        ui->type->setEnabled(true);
        ui->id2->setEnabled(true);
        ui->isID->setChecked(true);
        ui->inputAuthor->setEnabled(false);
        ui->inputPublicationYear->setEnabled(false);
        ui->inputTitle->setEnabled(false);
    }
}


void reserveWindow::on_isID_stateChanged(int state)
{
    if (state == Qt::Checked){
        ui->type->setEnabled(true);
        ui->isResource->setChecked(false);
        ui->id2->setEnabled(true);
    }

    else{
        ui->type->setEnabled(true);
        ui->isResource->setChecked(true);
        ui->id2->setEnabled(false);
    }
}


void reserveWindow::on_back_clicked()
{
    this->hide();
    mainwindow->show();
}


void reserveWindow::on_history_clicked()
{
    history = new reservationHistoryWindow(this);
    history->setAttribute(Qt::WA_DeleteOnClose);
    history->show();
}

void reserveWindow::on_delete_2_clicked()
{
    User* u;

    if (!currentUser->getAdmin()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete a Reservation",
                                      "To delete a reservation, you need access to an admin's account.\nContinue?",
                                      QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::No)
            return;

        if(reply == QMessageBox::Yes) {
            QString username = QInputDialog::getText(this, "Enter An Admin's Account Information", "Username:");
            QString pass = QInputDialog::getText(this, "", "Password:");
            int loginState = Library::mainLibrary().login(username.toStdString(), pass.toStdString()).first;
            if (loginState == 0) {
                QMessageBox::warning(this, "", "This is a regular account's information");
                return;
            }
            if (loginState == -1) {
                QMessageBox::warning(this, "", "Wrong Password");
                return;
            }
            if (loginState == -2) {
                QMessageBox::warning(this, "", "Wrong Username");
                return;
            }
        }
    }

    if (ui->currentUser->isChecked()) {
        u = currentUser;
    } else {
        int findUser;
        if (ui->isId->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->id->value());
        }
        else if (ui->isUsername->isChecked()){
            findUser = Library::mainLibrary().findUser(ui->username->text().toStdString());
        }
        else {
            QMessageBox::warning(this, "", "You need to provide the user's information");
            return;
        }

        if (findUser == -1) {
            QMessageBox::warning(this, "", "Given ID/username doesn't match an existing user");
            return;
        }

        if (Library::mainLibrary().libraryUsers[findUser].getAdmin()){
            QMessageBox::warning(this, "", "Can't reserve a resource as an admin");
            return;
        }

        if (currentUser->getAdmin() || Library::mainLibrary().libraryUsers[findUser].getPassword() == ui->password->text().toStdString()){
            u = &Library::mainLibrary().libraryUsers[findUser];
        }
        else {
            QMessageBox::warning(this, "Warning", "Entered password is wrong");
            return;
        }
    }

    if (!ui->book->isChecked() && !ui->article->isChecked() &&
        !ui->digitalcontent->isChecked() && !ui->other->isChecked())
    {
        QMessageBox::warning(this, "", "The resource's type must be provided");
        return;
    }

    if (ui->isResource->isChecked() && (ui->inputAuthor->text().isEmpty() || ui->inputTitle->text().isEmpty())){
        QMessageBox::warning(this, "", "All resource's information must be provided");
        return;
    }
    string type;
    if (ui->book->isChecked()){
        type = "Book";
    }
    else if (ui->article->isChecked()){
        type = "Article";
    }
    else if (ui->digitalcontent->isChecked()){
        type = "digital content";
    }
    else {
        type = "other";
    }

    if (ui->isID->isChecked()){
        pair<int,int> id = make_pair(Helper :: setRowIndex(type), ui->id2->value());
        Resource res = Library::mainLibrary().findResource(id);
        if (res == Resource("out of range", "out of range", 0)) {
            QMessageBox::warning(this, "Warning", "The given resource ID is out of range");
            return;
        }
        if (Library::mainLibrary().findReservation(*u, Library::mainLibrary().libraryResources[id.first][id.second]) == -1) {
            QMessageBox::warning(this, "", "This resource isn't reserved by the given user");
            return;
        }
        Library::mainLibrary().deleteReservation(*u, Library::mainLibrary().libraryResources[id.first][id.second]);
        QMessageBox::information(this, "Success", "Reservation deleted successfully");
        return;
    }

    if (ui->isResource->isChecked()){
        string title = ui->inputTitle->text().toStdString();
        string author = ui->inputAuthor->text().toStdString();
        int publicationYear = ui->inputPublicationYear->value();
        int quan = 0;
        Resource r(title, author, publicationYear, quan, type);

        pair<int,int> id = Library::mainLibrary().findResource(r);
        if (id == make_pair(-1, -1)) {
            QMessageBox::warning(this, "Warning", "The given resource's information is invalid");
            return;
        }
        if (Library::mainLibrary().findReservation(*u, Library::mainLibrary().libraryResources[id.first][id.second]) == -1) {
            QMessageBox::warning(this, "", "This resource isn't reserved by the given user");
            return;
        }
        Library::mainLibrary().deleteReservation(*u, Library::mainLibrary().libraryResources[id.first][id.second]);
        QMessageBox::information(this, "Success", "Reservation deleted successfully");
        return;
    }

    QMessageBox::warning(this, "", "No valid resource selection method was chosen");
}
