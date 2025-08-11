QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = ../bin

HEADERS += \
    src/interface/IApplicationView.h \
    src/interface/INodeView.h \
    src/interface/IViewFactory.h \
    src/model/ApplicationModel.h \
    src/model/ArbitageNodeModel.h \
    src/service/ModelFactory.h \
    src/common/Common.h \
    src/interface/IApplicationModel.h \
    src/interface/IModelFactory.h \
    src/interface/INodeModel.h \
    src/view/ApplicationView.h \
    src/view/ArbitrageNodeView.h

SOURCES += \
    src/model/ApplicationModel.cpp \
    src/model/ArbitageNodeModel.cpp \
    src/service/ModelFactory.cpp \
    src/main.cpp \
    src/view/ApplicationView.cpp \
    src/view/ArbitrageNodeView.cpp

INCLUDEPATH += \
    $$PWD/../AppSettingsLib \
    $$PWD/../SerializerLib \
    $$PWD/../RequesterLib

LIBS *= -L$$OUT_PWD/$$DESTDIR -lRequesterLib -lAppSettingsLib -lSerializerLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
