TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    splitter.cpp \
    storechain.cpp \
    storedatahandler.cpp

HEADERS += \
    storedatahandler.hpp \
    storechain.hpp \
    splitter.hpp

DISTFILES +=
