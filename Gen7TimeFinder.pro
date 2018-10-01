#-------------------------------------------------
#
# Project created by QtCreator 2018-09-30T12:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gen7TimeFinder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Forms/MainWindow.ui

HEADERS += \
    Forms/MainWindow.hpp \
    Header/SFMT.hpp \
    Header/IDSearcher.hpp \
    Models/IDModel.hpp \
    Views/IDView.hpp \
    Header/Utility.hpp

SOURCES += \
    Forms/MainWindow.cpp \
    Source/SFMT.cpp \
    main.cpp \
    Header/IDSearcher.cpp \
    Models/IDModel.cpp \
    Views/IDView.cpp \
    Header/Utility.cpp
