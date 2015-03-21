#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T01:33:15
#
#-------------------------------------------------
QT       += core gui
QT       +=network

TARGET = Carnivore
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    protocol_list.cpp \
    savedfilters.cpp \
    HardDiskManager.cpp \
    Adapter.cpp \
    WinpcapSniffer.cpp \
    WinpcapWrapper.cpp \
    systeminfo.cpp \
    callback-pcap.cpp \
    filters.cpp \
    #Style Code/stylesheet.cpp \
    stylesheet.cpp \
    report.cpp

HEADERS  += mainwindow.h \
    protocol_list.h \
    savedfilters.h \
    ../DiskManager - Copy/HardDiskManager/HardDiskManager.h \
    ../DiskManager - Copy/HardDiskManager/HardDiskManager.h \
    DESK_INFO/HardDiskManager.h \
    util/MEMORY_HANDEL.h \
    ../../G_Projects/GP Network anlysis/implemmentations/QT CONSOLE/HANDLE/HANDLE.h \
    Adapter.h \
    WinpcapSniffer.h \
    WinpcapWrapper.h \
    systeminfo.h \
    CallbackHandle.h \
    filters.h \
    #Style Code/stylesheet.h \
    #Style Code/stylesheet.h \
    stylesheet.h \
    report.h

FORMS    += mainwindow.ui \
    protocol_list.ui \
    savedfilters.ui \
    report.ui

RESOURCES += \
    ProjectRes.qrc

#win32:LIBS	+= -L C:\WpdPack\Lib -lwpcap
#win32:INCLUDEPATH	+= C:\WpdPack\include

INCLUDEPATH += C:\winpcap\Include
LIBS += C:\winpcap\Lib\wpcap.lib
LIBS += C:\QtSDK\mingw\lib\libws2_32.a

OTHER_FILES += \
    #Style Code/style.cdb \
    style.cdb
CONFIG += build_all
