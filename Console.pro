#-------------------------------------------------
#
# Project created by QtCreator 2013-02-10T13:22:41
#
#-------------------------------------------------

QT       -= gui
QT += script

TARGET = Console
TEMPLATE = lib

DEFINES += CONSOLE_LIBRARY

SOURCES += console.cpp \
   commandinterpreter.cpp \
   filelogger.cpp \
   qsignalcatcher.cpp

HEADERS += console.h\
   commandinterpreter.h \
   filelogger.h \
   qsignalcatcher.h \
        Console_global.h \
    helpers.h

OTHER_FILES += \
    flex.pri


macx {
LIBS += -L/usr/local/lib -lreadline.6.2 -lhistory.6.2
}

win32 {
LIBS += -lreadline -lhistory
# LIBS += -static-libgcc
}

FLEXSOURCES += cmd.l

include(flex.pri)
