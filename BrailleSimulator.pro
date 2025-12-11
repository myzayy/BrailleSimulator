TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        file_ops.c \
        main.c \
        translator.c

HEADERS += \
    braille.h \
    file_ops.h \
    translator.h
