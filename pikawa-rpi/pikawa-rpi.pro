QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    AnalyseSante.cpp \
    BaseDeDonnees.cpp \
    ChoixCapsule.cpp \
    GestionMachine.cpp \
    Pikawa.cpp \
    Utilisateur.cpp \
    main.cpp \
    ihmpikawa.cpp

HEADERS += \
    AnalyseSante.h \
    BaseDeDonnees.h \
    ChoixCapsule.h \
    GestionMachine.h \
    Pikawa.h \
    Utilisateur.h \
    ihmpikawa.h

FORMS += \
    ihmpikawa.ui

COPIES += bdd
bdd.files = pikawa.db
bdd.path = $$OUT_PWD/
bdd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
