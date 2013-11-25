TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    TestListe.c \
    AllTests.c \
    CuTest/CuTest.c \
    lib/liste.c

HEADERS += CuTest/CuTest.h \
    lib/liste.h

