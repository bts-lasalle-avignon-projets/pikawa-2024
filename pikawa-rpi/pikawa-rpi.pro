QT += core gui sql
QT += bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++11

SOURCES += \
    AnalyseSante.cpp \
    BaseDeDonnees.cpp \
    Communication.cpp \
    GestionMagasin.cpp \
    Utilisateur.cpp \
    main.cpp \
    ihmpikawa.cpp

HEADERS += \
    AnalyseSante.h \
    BaseDeDonnees.h \
    Communication.h \
    GestionMagasin.h \
    Utilisateur.h \
    ihmpikawa.h

FORMS += \
    ihmpikawa.ui

RESOURCES += pikawa-rpi.qrc

COPIES += bdd
bdd.files = pikawa.db
bdd.path = $$OUT_PWD/
bdd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
