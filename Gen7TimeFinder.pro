lessThan(QT_MAJOR_VERSION, 5): error("You need at least Qt 5.11 to build Gen7TimeFinder")
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 11): error("You need at least Qt 5.11 to build Gen7TimeFinder")

QT += widgets
CONFIG += c++1z

TARGET = Gen7TimeFinder
TEMPLATE = app
VERSION = 0.2.0

DEFINES += QT_DEPRECATED_WARNINGS

FORMS += \
    Forms/Controls/IVFilter.ui \
    Forms/MainWindow.ui \
    Forms/ProfileCalibrater.ui \
    Forms/ProfileEditor.ui \
    Forms/ProfileManager.ui

HEADERS += \
    Core/Game.hpp \
    Core/Global.hpp \
    Core/IDFilter.hpp \
    Core/IDSearcher.hpp \
    Core/ProfileSearcher.hpp \
    Core/SFMT.hpp \
    Core/StationaryFilter.hpp \
    Core/StationarySearcher.hpp \
    Core/Utility.hpp \
    Forms/Controls/CheckList.hpp \
    Forms/Controls/IVFilter.hpp \
    Forms/Controls/Label.hpp \
    Forms/Controls/TableView.hpp \
    Forms/Controls/TextBox.hpp \
    Forms/MainWindow.hpp \
    Forms/ProfileCalibrater.hpp \
    Forms/ProfileEditor.hpp \
    Forms/ProfileManager.hpp \
    Models/IDModel.hpp \
    Models/ProfileModel.hpp \
    Models/StationaryModel.hpp \
    Results/IDResult.hpp \
    Results/Profile.hpp \
    Results/StationaryResult.hpp

SOURCES += \
    Core/IDFilter.cpp \
    Core/IDSearcher.cpp \
    Core/ProfileSearcher.cpp \
    Core/SFMT.cpp \
    Core/StationaryFilter.cpp \
    Core/StationarySearcher.cpp \
    Core/Utility.cpp \
    Forms/Controls/CheckList.cpp \
    Forms/Controls/IVFilter.cpp \
    Forms/Controls/Label.cpp \
    Forms/Controls/TableView.cpp \
    Forms/Controls/TextBox.cpp \
    Forms/MainWindow.cpp \
    Forms/ProfileCalibrater.cpp \
    Forms/ProfileEditor.cpp \
    Forms/ProfileManager.cpp \
    Models/IDModel.cpp \
    Models/ProfileModel.cpp \
    Models/StationaryModel.cpp \
    Results/IDResult.cpp \
    Results/Profile.cpp \
    Results/StationaryResult.cpp \
    main.cpp


