#-------------------------------------------------
#
# Project created by QtCreator 2018-09-13T16:41:04
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = Vfp
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
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
        main.cpp \
        View/mainview.cpp \
    View/setuptab.cpp \
    utils.cpp \
    startup.cpp \
    Model/settings.cpp \
    Model/provider.cpp \
    Model/instsocket.cpp \
    ViewMgr/setupviewmanager.cpp \
    Model/instrument.cpp \
    View/controltab.cpp \
    ViewMgr/controlviewmanager.cpp \
    View/aboutbox.cpp

HEADERS += \
        View/mainview.h \
    View/setuptab.h \
    utils.h \
    startup.h \
    Model/settings.h \
    Model/provider.h \
    Model/instsocket.h \
    ViewMgr/setupviewmanager.h \
    Model/instrument.h \
    View/controltab.h \
    ViewMgr/controlviewmanager.h \
    View/aboutbox.h

FORMS += \
        View/mainview.ui \
    View/setuptab.ui \
    View/controltab.ui \
    View/aboutbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    vfprecources.qrc
