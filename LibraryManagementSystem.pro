TEMPLATE = app
TARGET   = LibraryManagementSystem

QT += core gui network widgets testlib
CONFIG += c++17

INCLUDEPATH += $$PWD/third_party
INCLUDEPATH += include


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/date.cpp \
    src/helper.cpp \
    src/library.cpp \
    src/resource.cpp \
    src/timee.cpp \
    src/user.cpp \
    src/windows/about.cpp \
    src/windows/addwindow.cpp \
    src/windows/borrowinghistorywindow.cpp \
    src/windows/borrowwindow.cpp \
    src/windows/editaboutwindow.cpp \
    src/windows/editwindow.cpp \
    src/windows/emailwindow.cpp \
    src/windows/findwindow.cpp \
    src/windows/librarymanagementsystem.cpp \
    src/windows/loginwindow.cpp \
    src/windows/removewindow.cpp \
    src/windows/reservationhistorywindow.cpp \
    src/windows/reservewindow.cpp \
    src/windows/useraddwindow.cpp \
    src/windows/usereditwindow.cpp \
    src/windows/userremovewindow.cpp \
    src/windows/userwindow.cpp \
    third_party/smtp/src/emailaddress.cpp \
    third_party/smtp/src/mimeattachment.cpp \
    third_party/smtp/src/mimebase64encoder.cpp \
    third_party/smtp/src/mimebase64formatter.cpp \
    third_party/smtp/src/mimebytearrayattachment.cpp \
    third_party/smtp/src/mimecontentencoder.cpp \
    third_party/smtp/src/mimecontentformatter.cpp \
    third_party/smtp/src/mimefile.cpp \
    third_party/smtp/src/mimehtml.cpp \
    third_party/smtp/src/mimeinlinefile.cpp \
    third_party/smtp/src/mimemessage.cpp \
    third_party/smtp/src/mimemultipart.cpp \
    third_party/smtp/src/mimepart.cpp \
    third_party/smtp/src/mimeqpencoder.cpp \
    third_party/smtp/src/mimeqpformatter.cpp \
    third_party/smtp/src/mimetext.cpp \
    third_party/smtp/src/quotedprintable.cpp \
    third_party/smtp/src/smtpclient.cpp


HEADERS += \
    include/date.h \
    include/email.h \
    include/event.h \
    include/helper.h \
    include/history.h \
    include/library.h \
    include/resource.h \
    include/timee.h \
    include/user.h \
    include/windows/about.h \
    include/windows/addwindow.h \
    include/windows/borrowinghistorywindow.h \
    include/windows/borrowwindow.h \
    include/windows/editaboutwindow.h \
    include/windows/editwindow.h \
    include/windows/emailwindow.h \
    include/windows/findwindow.h \
    include/windows/librarymanagementsystem.h \
    include/windows/loginwindow.h \
    include/windows/removewindow.h \
    include/windows/reservationhistorywindow.h \
    include/windows/reservewindow.h \
    include/windows/useraddwindow.h \
    include/windows/usereditwindow.h \
    include/windows/userremovewindow.h \
    include/windows/userwindow.h \
    third_party/smtp/src/SmtpMime \
    third_party/smtp/src/emailaddress.h \
    third_party/smtp/src/mimeattachment.h \
    third_party/smtp/src/mimebase64encoder.h \
    third_party/smtp/src/mimebase64formatter.h \
    third_party/smtp/src/mimebytearrayattachment.h \
    third_party/smtp/src/mimecontentencoder.h \
    third_party/smtp/src/mimecontentformatter.h \
    third_party/smtp/src/mimefile.h \
    third_party/smtp/src/mimehtml.h \
    third_party/smtp/src/mimeinlinefile.h \
    third_party/smtp/src/mimemessage.h \
    third_party/smtp/src/mimemultipart.h \
    third_party/smtp/src/mimepart.h \
    third_party/smtp/src/mimeqpencoder.h \
    third_party/smtp/src/mimeqpformatter.h \
    third_party/smtp/src/mimetext.h \
    third_party/smtp/src/quotedprintable.h \
    third_party/smtp/src/smtpclient.h \
    third_party/smtp/src/smtpmime_global.h



FORMS += \
    third_party/smtp/demos/demo2/sendemail.ui \
    ui/about.ui \
    ui/addwindow.ui \
    ui/borrowinghistorywindow.ui \
    ui/borrowwindow.ui \
    ui/editaboutwindow.ui \
    ui/editwindow.ui \
    ui/emailwindow.ui \
    ui/findwindow.ui \
    ui/librarymanagementsystem.ui \
    ui/loginwindow.ui \
    ui/removewindow.ui \
    ui/reservationhistorywindow.ui \
    ui/reservewindow.ui \
    ui/useraddwindow.ui \
    ui/usereditwindow.ui \
    ui/userremovewindow.ui \
    ui/userwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    build/Data/borrowingHistory.csv \
    build/Data/borrowingUsers.csv \
    build/Data/libraryEvents.csv \
    build/Data/libraryResources.csv \
    build/Data/openingSchedule.csv \
    build/Data/reservationUsers.csv \
    build/Data/users.csv \
    build/Media/add.png \
    build/Media/background.png \
    build/Media/backgroung.png \
    build/Media/borrow.png \
    build/Media/button.png \
    build/Media/delete.png \
    build/Media/edit.png \
    build/Media/find.png \
    build/Media/icon.png \
    build/Media/lineEditBackground.png \
    build/Media/loginWindow.png \
    build/Media/reserve.png \
    build/Media/textBg.png \
    build/Media/users.png \
    media/add.png \
    media/borrow.png \
    media/delete.png \
    media/edit.png \
    media/find.png \
    media/loginWindow.png \
    media/reserve.png \
    media/users.png \
    third_party/smtp/src/CMakeLists.txt

SUBDIRS += \
    third_party/smtp/src/SMTPEmail.pro \
    third_party/smtp/src/SMTPEmail.pro
