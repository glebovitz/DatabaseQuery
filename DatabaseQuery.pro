#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T15:15:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DatabaseQuery
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    databasedialog.cpp \
    defaults.cpp \
    database.cpp \
    insertdatabase.cpp \
    filterdialog.cpp \
    datastore.cpp \
    datastoremodel.cpp \
    databasequery.cpp \
    databasequeryrequest.cpp \
    mainwindowqueries.cpp \
    datanode.cpp

HEADERS  += mainwindow.h \
    databasedialog.h \
    defaults.h \
    querystrings.h \
    database.h \
    insertdatabase.h \
    filterdialog.h \
    datastore.h \
    datastoremodel.h \
    databasequery.h \
    databasequeryrequest.h \
    datanode.h

FORMS    += mainwindow.ui \
    databasedialog.ui \
    addonetimecharge.ui \
    filterdialog.ui

OTHER_FILES += \
    connectionStrings.csv
