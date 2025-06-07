#include "windows/librarymanagementsystem.h"
#include "windows/loginwindow.h"
#include <QApplication>
#include <QWidget>
#include <QIcon>
#include <QMessageBox>
#include <QProxyStyle>
#include <QStyle>
#include <QPixmap>
#include <QDebug>
#include <QDir>

class CustomMessageBoxStyle : public QProxyStyle {
public:
    QIcon standardIcon(StandardPixmap icon, const QStyleOption* option = nullptr,
                       const QWidget* widget = nullptr) const override {
        if (icon == QStyle::SP_MessageBoxWarning) {
            return QIcon(":/media/media/warning.png");
        }
        if (icon == QStyle::SP_MessageBoxInformation) {
            return QIcon(":/media/media/information.png");
        }
        return QProxyStyle::standardIcon(icon, option, widget);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("Monotype Corsiva", 17);
    QApplication::setFont(font);
    a.setWindowIcon(QIcon(":/media/media/icon.png"));
    a.setStyle(new CustomMessageBoxStyle);
    a.setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #eae0c2, stop: 1 #ccc2a6); "
        "background-color: #9e794f;"
        "border-radius: 15px;"
        "border: 2px solid #333029;"
        "color: white;"
        "font-family: Monotype Corsiva;"
        "font-size: 17px;"
        "font-weight: bold;"
        "padding: 4px 7px;"
        "text-decoration: none;"
        "}"

        "QPushButton:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccc2a6, stop: 1 #eae0c2);"
        "background-color: #ccc2a6;"
        "}"

        "QPushButton:pressed {"
        "position: relative;"
        "top: 1px;"
        "}"

        "QHeaderView::section {"
        "background-image: url(:/media/media/tableHeaderBG.png);"
        "color: white;"
        "border: 1px solid #666;"
        "padding: 5px;"
        "font-family: Times New Roman,serif;"
        "font-size: 13px;"
        "}"

        );
    LibraryManagementSystem mainWin;
    loginWindow login(&mainWin);
    login.show();

    return a.exec();

}
