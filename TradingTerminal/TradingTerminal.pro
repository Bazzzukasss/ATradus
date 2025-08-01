QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = ../bin

HEADERS += \

SOURCES += \
    src/main.cpp

INCLUDEPATH += \
    $$PWD/../AppSettingsLib/src \
    $$PWD/../SerializerLib/src \
    $$PWD/../RequesterLib/src \
    $$PWD/../RequesterLib/src/common \
    $$PWD/../RequesterLib/src/interfaces \
    $$PWD/../RequesterLib/src/binance \
    $$PWD/../RequesterLib/src/client

LIBS *= -L$$OUT_PWD/$$DESTDIR -lRequesterLib -lAppSettingsLib -lSerializerLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
