QT += core
QT -= gui
QT += dbus

TARGET = file_caca
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cfiles.cpp \
    cphotodiode.cpp \
    cpsd.cpp \
    comdbus.cpp


HEADERS += \
    cfiles.h \
    cphotodiode.h \
    cpsd.h \
    comdbus.h

target.path= /usr/bin


dbus-etc.files = dbus/amplitude.systemes.service.warptool.conf
dbus-etc.path = /etc/dbus-1/system.d/

dbus-usr.files = dbus/amplitude.service.warptool.service
dbus-usr.path = /usr/share/dbus-1/system-services/

target.path= /usr/bin

INSTALLS += target dbus-etc dbus-usr
