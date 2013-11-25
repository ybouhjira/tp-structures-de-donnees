TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    TestListe.c \
    AllTests.c \
    CuTest/CuTest.c \
    lib/liste.cpp

HEADERS += CuTest/CuTest.h \
    lib/liste.h

