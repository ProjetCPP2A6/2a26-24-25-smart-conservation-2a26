QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET= projetApplication

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comm_prod.cpp \
    commandes.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    produits.cpp

HEADERS += \
    comm_prod.h \
    commandes.h \
    connection.h \
    mainwindow.h \
    produits.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
