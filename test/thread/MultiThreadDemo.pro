QT += core
QT -= gui

TARGET = MultiThreadDemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include (/home/huangcf/document/frameworks/logging/logging.pri)

SOURCES += main.cpp \
    mythread.cpp \
    mycontroller.cpp

HEADERS += \
    mythread.h \
    mycontroller.h

