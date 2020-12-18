QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcgaugewidget.cpp \
    UAVairQuality.pb.c \
    pb/pb_common.c \
    pb/pb_decode.c \
    pb/pb_encode.c


HEADERS += \
    mainwindow.h \
    qcgaugewidget.h \
    pb/pb_common.h \
    pb/pb_decode.h \
    pb/pb_encode.h \
    pb/pb.h \
    UAVairQuality.pb.h \
    uavairqualityprotocol.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
