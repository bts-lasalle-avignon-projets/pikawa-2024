QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    AnalyseSante.cpp \
    ChoixCapsule.cpp \
    GestionMachine.cpp \
    Pikawa.cpp \
    Utilisateur.cpp \
    main.cpp \
    ihmpikawa.cpp

HEADERS += \
    AnalyseSante.h \
    ChoixCapsule.h \
    GestionMachine.h \
    Pikawa.h \
    Utilisateur.h \
    ihmpikawa.h

FORMS += \
    ihmpikawa.ui

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
