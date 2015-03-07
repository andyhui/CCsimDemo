#############################################################################
# Makefile for building: CCSimDemo
# Generated by qmake (2.01a) (Qt 4.8.1) on: Sat Mar 7 13:25:49 2015
# Project:  CCSimDemo.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile CCSimDemo.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = node_item.cpp \
		bullet_item.cpp \
		sim_scene.cpp \
		main.cpp \
		BEcharToDouble.cpp \
		getSendMsg.cpp \
		IpToChar.cpp \
		parseRecvMsg.cpp \
		recieveMsg.cpp \
		sendMsg.cpp \
		mainwindow.cpp \
		titlebar/frame.cpp \
		titlebar/titlebar.cpp moc_mainwindow.cpp \
		moc_titlebar.cpp \
		qrc_CCSimDemo.cpp
OBJECTS       = node_item.o \
		bullet_item.o \
		sim_scene.o \
		main.o \
		BEcharToDouble.o \
		getSendMsg.o \
		IpToChar.o \
		parseRecvMsg.o \
		recieveMsg.o \
		sendMsg.o \
		mainwindow.o \
		frame.o \
		titlebar.o \
		moc_mainwindow.o \
		moc_titlebar.o \
		qrc_CCSimDemo.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		CCSimDemo.pro
QMAKE_TARGET  = CCSimDemo
DESTDIR       = 
TARGET        = CCSimDemo

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

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: CCSimDemo.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtNetwork.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile CCSimDemo.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtNetwork.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile CCSimDemo.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/CCSimDemo1.0.0 || $(MKDIR) .tmp/CCSimDemo1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/CCSimDemo1.0.0/ && $(COPY_FILE) --parents mainwindow.h node_item.h bullet_item.h sim_scene.h titlebar/frame.h titlebar/titlebar.h .tmp/CCSimDemo1.0.0/ && $(COPY_FILE) --parents CCSimDemo.qrc .tmp/CCSimDemo1.0.0/ && $(COPY_FILE) --parents node_item.cpp bullet_item.cpp sim_scene.cpp main.cpp BEcharToDouble.cpp getSendMsg.cpp IpToChar.cpp parseRecvMsg.cpp recieveMsg.cpp sendMsg.cpp mainwindow.cpp titlebar/frame.cpp titlebar/titlebar.cpp .tmp/CCSimDemo1.0.0/ && (cd `dirname .tmp/CCSimDemo1.0.0` && $(TAR) CCSimDemo1.0.0.tar CCSimDemo1.0.0 && $(COMPRESS) CCSimDemo1.0.0.tar) && $(MOVE) `dirname .tmp/CCSimDemo1.0.0`/CCSimDemo1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/CCSimDemo1.0.0


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

compiler_moc_header_make_all: moc_mainwindow.cpp moc_titlebar.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_titlebar.cpp
moc_mainwindow.cpp: node_item.h \
		bullet_item.h \
		sim_scene.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_titlebar.cpp: titlebar/titlebar.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) titlebar/titlebar.h -o moc_titlebar.cpp

compiler_rcc_make_all: qrc_CCSimDemo.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_CCSimDemo.cpp
qrc_CCSimDemo.cpp: CCSimDemo.qrc \
		images/open.png \
		images/button-hover.png \
		images/find.png \
		images/background1.png \
		images/gotocell.png \
		images/darkgray.png \
		images/button.png \
		images/paste.png \
		images/main-background.png \
		images/save.png \
		images/button-bak.png \
		images/icon.png \
		images/down-arrow.png \
		images/button-pressed.png \
		images/gray.png \
		images/background.png \
		images/green.png \
		images/new.png \
		images/copy.png \
		images/cut.png \
		images/plane.png \
		images/toolbutton.png \
		Maps/map1.png \
		Maps/map2.png \
		Maps/map3.png \
		Maps/map4.png \
		Maps/map5.png \
		Icons/star.png \
		Icons/target.png \
		Icons/red.png \
		Icons/attack.png \
		Icons/blue.png \
		Icons/enemy_damage.png \
		Icons/friend_damage.png \
		Icons/neutral_damage.png \
		Icons/black.png
	/usr/bin/rcc -name CCSimDemo CCSimDemo.qrc -o qrc_CCSimDemo.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

node_item.o: node_item.cpp node_item.h \
		sim_scene.h \
		bullet_item.h \
		mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o node_item.o node_item.cpp

bullet_item.o: bullet_item.cpp bullet_item.h \
		node_item.h \
		sim_scene.h \
		mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bullet_item.o bullet_item.cpp

sim_scene.o: sim_scene.cpp sim_scene.h \
		bullet_item.h \
		node_item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sim_scene.o sim_scene.cpp

main.o: main.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h \
		titlebar/frame.h \
		titlebar/titlebar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

BEcharToDouble.o: BEcharToDouble.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o BEcharToDouble.o BEcharToDouble.cpp

getSendMsg.o: getSendMsg.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o getSendMsg.o getSendMsg.cpp

IpToChar.o: IpToChar.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o IpToChar.o IpToChar.cpp

parseRecvMsg.o: parseRecvMsg.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parseRecvMsg.o parseRecvMsg.cpp

recieveMsg.o: recieveMsg.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o recieveMsg.o recieveMsg.cpp

sendMsg.o: sendMsg.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sendMsg.o sendMsg.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		node_item.h \
		bullet_item.h \
		sim_scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

frame.o: titlebar/frame.cpp titlebar/frame.h \
		titlebar/titlebar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o frame.o titlebar/frame.cpp

titlebar.o: titlebar/titlebar.cpp titlebar/titlebar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o titlebar.o titlebar/titlebar.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_titlebar.o: moc_titlebar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_titlebar.o moc_titlebar.cpp

qrc_CCSimDemo.o: qrc_CCSimDemo.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_CCSimDemo.o qrc_CCSimDemo.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

