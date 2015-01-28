QMAKE_CXXFLAGS+= -std=c++11
INCLUDEPATH+= ..
LIBS+=-L$$PWD/../dumpwrapper -ldumpwrapper
QT       -= gui
TARGET = prepair_dump_app
TEMPLATE = app
SOURCES += main.cpp
