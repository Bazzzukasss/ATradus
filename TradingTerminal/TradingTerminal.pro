QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = ../bin

HEADERS += \
    src/MainWindow.h \
    src/interface/IApplicationView.h \
    src/interface/IArbitrageNodeModel.h \
    src/interface/IArbitrageNodeView.h \
    src/interface/INodeListModel.h \
    src/interface/INodeListView.h \
    src/interface/INodeView.h \
    src/interface/IViewFactory.h \
    src/model/ApplicationModel.h \
    src/model/ArbitageNodeModel.h \
    src/model/NodeListModel.h \
    src/service/ModelFactory.h \
    src/common/Common.h \
    src/interface/IApplicationModel.h \
    src/interface/IModelFactory.h \
    src/interface/INodeModel.h \
    src/service/ViewFactory.h \
    src/view/ApplicationView.h \
    src/view/ArbitrageNodeView.h \
    src/view/NodeListView.h \
    src/view/NodeView.h

SOURCES += \
    src/MainWindow.cpp \
    src/model/ApplicationModel.cpp \
    src/model/ArbitageNodeModel.cpp \
    src/model/NodeListModel.cpp \
    src/service/ModelFactory.cpp \
    src/main.cpp \
    src/service/ViewFactory.cpp \
    src/view/ApplicationView.cpp \
    src/view/ArbitrageNodeView.cpp \
    src/view/NodeListView.cpp \
    src/view/NodeView.cpp

INCLUDEPATH += \
    $$PWD/../AppSettingsLib \
    $$PWD/../SerializerLib \
    $$PWD/../RequesterLib

LIBS *= -L$$OUT_PWD/$$DESTDIR -lRequesterLib -lAppSettingsLib -lSerializerLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
