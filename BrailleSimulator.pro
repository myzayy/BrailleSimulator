TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        file_ops.c \
        main.c \
        printer.c \
        translator.c

HEADERS += \
    braille.h \
    file_ops.h \
    printer.h \
    translator.h
