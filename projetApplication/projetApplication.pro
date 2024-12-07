QT       += core gui sql
QT += core gui charts
QT += serialport
QT += printsupport
QT+= sql
QT += widgets sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET= projetApplication

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    commandes.cpp \
    connection.cpp \
    cuiss_ing.cpp \
    deliver.cpp \
    main.cpp \
    mainwindow.cpp \
    matieres_premieres.cpp \
    ravi_ing.cpp \
    ravitaillements.cpp

HEADERS += \
    arduino.h \
    commandes.h \
    connection.h \
    cuiss_ing.h \
    deliver.h \
    mainwindow.h \
    matieres_premieres.h \
    ravi_ing.h \
    ravitaillements.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
