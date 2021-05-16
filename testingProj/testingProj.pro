include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS += \
        ../src/MarshalJson.hpp

SOURCES += \
        ../src/MarshalJson.cpp \
        main.cpp \
        test.cpp

DESTDIR = $$PWD/bin
