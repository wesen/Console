#############################################################################
# Makefile for building: Console
# Generated by qmake (2.01a) (Qt 4.8.4) on: Sun May 5 23:58:47 2013
# Project:  Console.pro
# Template: app
# Command: /usr/local/qt/qt-everywhere-opensource-src-4.8.4/bin/qmake -spec /usr/local/qt/mkspecs/unsupported/macx-clang CONFIG+=x86_64 CONFIG+=declarative_debug -o Makefile Console.pro
#############################################################################

####### Compiler, tools and options

CC            = clang
CXX           = clang++
DEFINES       = -DCONSOLE_LIBRARY -DQT_SCRIPT_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -arch x86_64 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -isystem/usr/local/qt/include -g -gdwarf-2 -arch x86_64 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/qt/mkspecs/unsupported/macx-clang -I. -I/usr/local/qt/include/QtCore -I/usr/local/qt/include/QtGui -I/usr/local/qt/include/QtScript -I/usr/local/qt/include -I-I/usr/local/opt/flex/include -Ivendor/qextserialport/src -I.
LINK          = clang++
LFLAGS        = -headerpad_max_install_names -arch x86_64
LIBS          = $(SUBLIBS)  -L/usr/local/qt/lib -L/usr/local/lib -lreadline.6.2 -lhistory.6.2 -L/usr/local/opt/flex/lib -lfl -framework IOKit -framework CoreFoundation -lQtScript_debug -L/usr/local/qt/lib -lQtGui_debug -lQtCore_debug 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/local/qt/qt-everywhere-opensource-src-4.8.4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = console.cpp \
		commandinterpreter.cpp \
		filelogger.cpp \
		qsignalcatcher.cpp \
		lcdinterpreter.cpp \
		vendor/lz4.c \
		main.cpp \
		helpers.cpp \
		vendor/qextserialport/src/qextserialport.cpp \
		vendor/qextserialport/src/qextserialenumerator.cpp \
		vendor/qextserialport/src/qextserialport_unix.cpp \
		vendor/qextserialport/src/qextserialenumerator_osx.cpp cmd.cpp \
		moc_console.cpp \
		moc_commandinterpreter.cpp \
		moc_filelogger.cpp \
		moc_qsignalcatcher.cpp \
		moc_lcdinterpreter.cpp
OBJECTS       = console.o \
		commandinterpreter.o \
		filelogger.o \
		qsignalcatcher.o \
		lcdinterpreter.o \
		lz4.o \
		main.o \
		helpers.o \
		qextserialport.o \
		qextserialenumerator.o \
		qextserialport_unix.o \
		qextserialenumerator_osx.o \
		cmd.o \
		moc_console.o \
		moc_commandinterpreter.o \
		moc_filelogger.o \
		moc_qsignalcatcher.o \
		moc_lcdinterpreter.o
DIST          = /usr/local/qt/mkspecs/common/unix.conf \
		/usr/local/qt/mkspecs/common/mac.conf \
		/usr/local/qt/mkspecs/common/gcc-base.conf \
		/usr/local/qt/mkspecs/common/gcc-base-macx.conf \
		/usr/local/qt/mkspecs/common/clang.conf \
		/usr/local/qt/mkspecs/qconfig.pri \
		/usr/local/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/qt/mkspecs/features/qt_functions.prf \
		/usr/local/qt/mkspecs/features/qt_config.prf \
		/usr/local/qt/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt/mkspecs/features/default_pre.prf \
		/usr/local/qt/mkspecs/features/mac/default_pre.prf \
		flex.pri \
		vendor/qextserialport/src/qextserialport.pri \
		/usr/local/qt/mkspecs/features/mac/dwarf2.prf \
		/usr/local/qt/mkspecs/features/debug.prf \
		/usr/local/qt/mkspecs/features/default_post.prf \
		/usr/local/qt/mkspecs/features/mac/default_post.prf \
		/usr/local/qt/mkspecs/features/mac/x86_64.prf \
		/usr/local/qt/mkspecs/features/mac/objective_c.prf \
		/usr/local/qt/mkspecs/features/declarative_debug.prf \
		/usr/local/qt/mkspecs/features/warn_on.prf \
		/usr/local/qt/mkspecs/features/qt.prf \
		/usr/local/qt/mkspecs/features/unix/thread.prf \
		/usr/local/qt/mkspecs/features/moc.prf \
		/usr/local/qt/mkspecs/features/mac/rez.prf \
		/usr/local/qt/mkspecs/features/mac/sdk.prf \
		/usr/local/qt/mkspecs/features/resources.prf \
		/usr/local/qt/mkspecs/features/uic.prf \
		/usr/local/qt/mkspecs/features/yacc.prf \
		/usr/local/qt/mkspecs/features/lex.prf \
		/usr/local/qt/mkspecs/features/include_source_dir.prf \
		Console.pro
QMAKE_TARGET  = Console
DESTDIR       = 
TARGET        = Console

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-arch \
		x86_64 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): cmd.cpp $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Console.pro  /usr/local/qt/mkspecs/unsupported/macx-clang/qmake.conf /usr/local/qt/mkspecs/common/unix.conf \
		/usr/local/qt/mkspecs/common/mac.conf \
		/usr/local/qt/mkspecs/common/gcc-base.conf \
		/usr/local/qt/mkspecs/common/gcc-base-macx.conf \
		/usr/local/qt/mkspecs/common/clang.conf \
		/usr/local/qt/mkspecs/qconfig.pri \
		/usr/local/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/qt/mkspecs/features/qt_functions.prf \
		/usr/local/qt/mkspecs/features/qt_config.prf \
		/usr/local/qt/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt/mkspecs/features/default_pre.prf \
		/usr/local/qt/mkspecs/features/mac/default_pre.prf \
		flex.pri \
		vendor/qextserialport/src/qextserialport.pri \
		/usr/local/qt/mkspecs/features/mac/dwarf2.prf \
		/usr/local/qt/mkspecs/features/debug.prf \
		/usr/local/qt/mkspecs/features/default_post.prf \
		/usr/local/qt/mkspecs/features/mac/default_post.prf \
		/usr/local/qt/mkspecs/features/mac/x86_64.prf \
		/usr/local/qt/mkspecs/features/mac/objective_c.prf \
		/usr/local/qt/mkspecs/features/declarative_debug.prf \
		/usr/local/qt/mkspecs/features/warn_on.prf \
		/usr/local/qt/mkspecs/features/qt.prf \
		/usr/local/qt/mkspecs/features/unix/thread.prf \
		/usr/local/qt/mkspecs/features/moc.prf \
		/usr/local/qt/mkspecs/features/mac/rez.prf \
		/usr/local/qt/mkspecs/features/mac/sdk.prf \
		/usr/local/qt/mkspecs/features/resources.prf \
		/usr/local/qt/mkspecs/features/uic.prf \
		/usr/local/qt/mkspecs/features/yacc.prf \
		/usr/local/qt/mkspecs/features/lex.prf \
		/usr/local/qt/mkspecs/features/include_source_dir.prf \
		/usr/local/qt/lib/libQtScript_debug.prl \
		/usr/local/qt/lib/libQtCore_debug.prl \
		/usr/local/qt/lib/libQtGui_debug.prl
	$(QMAKE) -spec /usr/local/qt/mkspecs/unsupported/macx-clang CONFIG+=x86_64 CONFIG+=declarative_debug -o Makefile Console.pro
/usr/local/qt/mkspecs/common/unix.conf:
/usr/local/qt/mkspecs/common/mac.conf:
/usr/local/qt/mkspecs/common/gcc-base.conf:
/usr/local/qt/mkspecs/common/gcc-base-macx.conf:
/usr/local/qt/mkspecs/common/clang.conf:
/usr/local/qt/mkspecs/qconfig.pri:
/usr/local/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/local/qt/mkspecs/features/qt_functions.prf:
/usr/local/qt/mkspecs/features/qt_config.prf:
/usr/local/qt/mkspecs/features/exclusive_builds.prf:
/usr/local/qt/mkspecs/features/default_pre.prf:
/usr/local/qt/mkspecs/features/mac/default_pre.prf:
flex.pri:
vendor/qextserialport/src/qextserialport.pri:
/usr/local/qt/mkspecs/features/mac/dwarf2.prf:
/usr/local/qt/mkspecs/features/debug.prf:
/usr/local/qt/mkspecs/features/default_post.prf:
/usr/local/qt/mkspecs/features/mac/default_post.prf:
/usr/local/qt/mkspecs/features/mac/x86_64.prf:
/usr/local/qt/mkspecs/features/mac/objective_c.prf:
/usr/local/qt/mkspecs/features/declarative_debug.prf:
/usr/local/qt/mkspecs/features/warn_on.prf:
/usr/local/qt/mkspecs/features/qt.prf:
/usr/local/qt/mkspecs/features/unix/thread.prf:
/usr/local/qt/mkspecs/features/moc.prf:
/usr/local/qt/mkspecs/features/mac/rez.prf:
/usr/local/qt/mkspecs/features/mac/sdk.prf:
/usr/local/qt/mkspecs/features/resources.prf:
/usr/local/qt/mkspecs/features/uic.prf:
/usr/local/qt/mkspecs/features/yacc.prf:
/usr/local/qt/mkspecs/features/lex.prf:
/usr/local/qt/mkspecs/features/include_source_dir.prf:
/usr/local/qt/lib/libQtScript_debug.prl:
/usr/local/qt/lib/libQtCore_debug.prl:
/usr/local/qt/lib/libQtGui_debug.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/qt/mkspecs/unsupported/macx-clang CONFIG+=x86_64 CONFIG+=declarative_debug -o Makefile Console.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Console1.0.0 || $(MKDIR) .tmp/Console1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Console1.0.0/ && $(COPY_FILE) --parents cmd.l .tmp/Console1.0.0/ && $(COPY_FILE) --parents console.h commandinterpreter.h filelogger.h qsignalcatcher.h Console_global.h helpers.h lcdinterpreter.h vendor/lz4.h vendor/qextserialport/src/qextserialport.h vendor/qextserialport/src/qextserialenumerator.h vendor/qextserialport/src/qextserialport_global.h vendor/qextserialport/src/qextserialport_p.h vendor/qextserialport/src/qextserialenumerator_p.h .tmp/Console1.0.0/ && $(COPY_FILE) --parents console.cpp commandinterpreter.cpp filelogger.cpp qsignalcatcher.cpp lcdinterpreter.cpp vendor/lz4.c main.cpp helpers.cpp vendor/qextserialport/src/qextserialport.cpp vendor/qextserialport/src/qextserialenumerator.cpp vendor/qextserialport/src/qextserialport_unix.cpp vendor/qextserialport/src/qextserialenumerator_osx.cpp .tmp/Console1.0.0/ && (cd `dirname .tmp/Console1.0.0` && $(TAR) Console1.0.0.tar Console1.0.0 && $(COMPRESS) Console1.0.0.tar) && $(MOVE) `dirname .tmp/Console1.0.0`/Console1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Console1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_flex_make_all: cmd.cpp
compiler_flex_clean:
	-$(DEL_FILE) cmd.cpp
cmd.cpp: cmd.l
	flex -o cmd.cpp cmd.l

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_console.cpp moc_commandinterpreter.cpp moc_filelogger.cpp moc_qsignalcatcher.cpp moc_lcdinterpreter.cpp moc_qextserialport.cpp moc_qextserialenumerator.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_console.cpp moc_commandinterpreter.cpp moc_filelogger.cpp moc_qsignalcatcher.cpp moc_lcdinterpreter.cpp moc_qextserialport.cpp moc_qextserialenumerator.cpp
moc_console.cpp: commandinterpreter.h \
		filelogger.h \
		console.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ console.h -o moc_console.cpp

moc_commandinterpreter.cpp: filelogger.h \
		commandinterpreter.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ commandinterpreter.h -o moc_commandinterpreter.cpp

moc_filelogger.cpp: filelogger.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ filelogger.h -o moc_filelogger.cpp

moc_qsignalcatcher.cpp: qsignalcatcher.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ qsignalcatcher.h -o moc_qsignalcatcher.cpp

moc_lcdinterpreter.cpp: commandinterpreter.h \
		filelogger.h \
		lcdinterpreter.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ lcdinterpreter.h -o moc_lcdinterpreter.cpp

moc_qextserialport.cpp: vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialport.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ vendor/qextserialport/src/qextserialport.h -o moc_qextserialport.cpp

moc_qextserialenumerator.cpp: vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialenumerator.h
	/usr/local/qt/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ vendor/qextserialport/src/qextserialenumerator.h -o moc_qextserialenumerator.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_flex_clean compiler_moc_header_clean 

####### Compile

console.o: console.cpp console.h \
		commandinterpreter.h \
		filelogger.h \
		helpers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o console.o console.cpp

commandinterpreter.o: commandinterpreter.cpp helpers.h \
		console.h \
		commandinterpreter.h \
		filelogger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o commandinterpreter.o commandinterpreter.cpp

filelogger.o: filelogger.cpp filelogger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o filelogger.o filelogger.cpp

qsignalcatcher.o: qsignalcatcher.cpp qsignalcatcher.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qsignalcatcher.o qsignalcatcher.cpp

lcdinterpreter.o: lcdinterpreter.cpp lcdinterpreter.h \
		commandinterpreter.h \
		filelogger.h \
		helpers.h \
		vendor/lz4.h \
		vendor/qextserialport/src/qextserialport.h \
		vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialenumerator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lcdinterpreter.o lcdinterpreter.cpp

lz4.o: vendor/lz4.c vendor/lz4.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o lz4.o vendor/lz4.c

main.o: main.cpp console.h \
		commandinterpreter.h \
		filelogger.h \
		lcdinterpreter.h \
		qsignalcatcher.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

helpers.o: helpers.cpp helpers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o helpers.o helpers.cpp

qextserialport.o: vendor/qextserialport/src/qextserialport.cpp vendor/qextserialport/src/qextserialport.h \
		vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialport_p.h \
		moc_qextserialport.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qextserialport.o vendor/qextserialport/src/qextserialport.cpp

qextserialenumerator.o: vendor/qextserialport/src/qextserialenumerator.cpp vendor/qextserialport/src/qextserialenumerator.h \
		vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialenumerator_p.h \
		moc_qextserialenumerator.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qextserialenumerator.o vendor/qextserialport/src/qextserialenumerator.cpp

qextserialport_unix.o: vendor/qextserialport/src/qextserialport_unix.cpp vendor/qextserialport/src/qextserialport.h \
		vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialport_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qextserialport_unix.o vendor/qextserialport/src/qextserialport_unix.cpp

qextserialenumerator_osx.o: vendor/qextserialport/src/qextserialenumerator_osx.cpp vendor/qextserialport/src/qextserialenumerator.h \
		vendor/qextserialport/src/qextserialport_global.h \
		vendor/qextserialport/src/qextserialenumerator_p.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qextserialenumerator_osx.o vendor/qextserialport/src/qextserialenumerator_osx.cpp

cmd.o: cmd.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cmd.o cmd.cpp

moc_console.o: moc_console.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_console.o moc_console.cpp

moc_commandinterpreter.o: moc_commandinterpreter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_commandinterpreter.o moc_commandinterpreter.cpp

moc_filelogger.o: moc_filelogger.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_filelogger.o moc_filelogger.cpp

moc_qsignalcatcher.o: moc_qsignalcatcher.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qsignalcatcher.o moc_qsignalcatcher.cpp

moc_lcdinterpreter.o: moc_lcdinterpreter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_lcdinterpreter.o moc_lcdinterpreter.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

