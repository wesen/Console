#-------------------------------------------------
#
# Project created by QtCreator 2013-02-10T13:22:41
#
#-------------------------------------------------

QT       += gui
QT += script core

TARGET = Console
TEMPLATE = app
CONFIG += console exceptions
CONFIG -= app_bundle

DEFINES += CONSOLE_LIBRARY

SOURCES += console.cpp \
   commandinterpreter.cpp \
   filelogger.cpp \
   qsignalcatcher.cpp \
    lcdinterpreter.cpp \
    vendor/lz4.c \
    main.cpp \
    helpers.cpp

HEADERS += console.h\
   commandinterpreter.h \
   filelogger.h \
   qsignalcatcher.h \
        Console_global.h \
    helpers.h \
    lcdinterpreter.h \
    vendor/lz4.h

OTHER_FILES += \
    flex.pri


macx {
LIBS += -L/usr/local/lib -lreadline.6.2 -lhistory.6.2
}

win32 {
    LIBS += -lreadline -lhistory
    LIBS += -L$$PWD/vendor/win32/lib
    DESTDIR_WIN = $$DESTDIR
    DESTDIR_WIN ~= s,/,\\,g
    EXTRA_BINFILES += $$PWD/vendor/win32/bin/*.dll
    EXTRA_BINFILES ~= s,/,\\,g
    for(FILE, EXTRA_BINFILES) {
        QMAKE_POST_LINK += $$quote(copy /y \"$${FILE}\" \"$${DESTDIR_WIN}\"$$escape_expand(\\n\\t))
    }
# LIBS += -static-libgcc
}

FLEXSOURCES += cmd.l

include(flex.pri)

include(vendor/qextserialport/src/qextserialport.pri)
