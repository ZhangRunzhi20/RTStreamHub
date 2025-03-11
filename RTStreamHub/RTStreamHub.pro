QT += core
QT -= gui

CONFIG += c++11

TARGET = RTStreamHub
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lssl -lcrypto

SOURCES += main.cpp \
    QStrSvr.cpp \
    ../src/convgpx.c \
    ../src/convkml.c \
    ../src/convrnx.c \
    ../src/datum.c \
    ../src/download.c \
    ../src/ephemeris.c \
    ../src/geoid.c \
    ../src/gis.c \
    ../src/ionex.c \
    ../src/lambda.c \
    ../src/options.c \
    ../src/pntpos.c \
    ../src/postpos.c \
    ../src/ppp.c \
    ../src/ppp_ar.c \
    ../src/preceph.c \
    ../src/rcvraw.c \
    ../src/rinex.c \
    ../src/rtcm.c \
    ../src/rtcm2.c \
    ../src/rtcm3.c \
    ../src/rtcm3e.c \
    ../src/rtkcmn.c \
    ../src/rtkpos.c \
    ../src/rtksvr.c \
    ../src/sbas.c \
    ../src/solution.c \
    ../src/stream.c \
    ../src/streamsvr.c \
    ../src/tides.c \
    ../src/tle.c \
    ../src/rcv/binex.c \
    ../src/rcv/crescent.c \
    ../src/rcv/javad.c \
    ../src/rcv/novatel.c \
    ../src/rcv/nvs.c \
    ../src/rcv/rt17.c \
    ../src/rcv/septentrio.c \
    ../src/rcv/skytraq.c \
    ../src/rcv/ss2.c \
    ../src/rcv/ublox.c

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    QStrSvr.h \
    rtklib.h
DEFINES += TRACE SVR_REUSEADDR


