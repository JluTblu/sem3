QT += core gui widgets

TARGET = phonebook
TEMPLATE = app

HEADERS += \
    headers/Contact.h \
    headers/ContactDialog.h \
    headers/PhoneBook.h

SOURCES += \
    src/Contact.cpp \
    src/ContactDialog.cpp \
    src/PhoneBook.cpp \
    src/main.cpp
