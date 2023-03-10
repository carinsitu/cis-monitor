#-------------------------------------------------
#
# Project created by QtCreator 2019-05-21T20:33:19
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets
QT       += mqtt
QT       += dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = carmonitor
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

SOURCES += \
        carmonitor.cpp \
        cockpit.cpp \
        cockpitheadsetview.cpp \
        cockpitmonitor.cpp \
        cockpitmonitorview.cpp \
        main.cpp \
        osdspeedcounter.cpp \
        osdspeedindicator.cpp \
        osdspeedindicatorclip.cpp \
        soundplayer.cpp \
        videoinputitem.cpp

HEADERS += \
        carmonitor.h \
        cockpit.h \
        cockpitheadsetview.h \
        cockpitmonitor.h \
        cockpitmonitorview.h \
        osdspeedcounter.h \
        osdspeedindicator.h \
        osdspeedindicatorclip.h \
        soundplayer.h \
        videoinputitem.h

FORMS += \
        carmonitor.ui

# Custom commands
lint.commands = \
        clang-format -i $$HEADERS $$SOURCES

QMAKE_EXTRA_TARGETS += lint

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

LIBS += -lopenal
LIBS += -lalut

