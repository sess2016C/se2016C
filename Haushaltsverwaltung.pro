#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T12:01:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Haushaltsverwaltung
TEMPLATE = app


SOURCES += main.cpp\
        haushaltsverwaltung.cpp \
    hauptmenue.cpp \
    erfassen.cpp \
    abrechnung.cpp \
    bezahlart.cpp \
    benutzerdaten.cpp \
    benutzerverwaltung.cpp \
    hauptmenue_adm.cpp \
    kategorieverwaltung.cpp \
    erstanmeldung_adm.cpp \
    dbmanager.cpp \
    newpassword.cpp \
    transaktion.cpp \
    zahlungsart.cpp \
    kategorie.cpp \
    benutzer.cpp \
    administrator.cpp \
    transaktionsliste.cpp

HEADERS  += haushaltsverwaltung.h \
    hauptmenue.h \
    erfassen.h \
    abrechnung.h \
    bezahlart.h \
    benutzerdaten.h \
    benutzerverwaltung.h \
    hauptmenue_adm.h \
    kategorieverwaltung.h \
    erstanmeldung_adm.h \
    dbmanager.h \
    global.h \
    newpassword.h \
    transaktion.h \
    zahlungsart.h \
    kategorie.h \
    benutzer.h \
    administrator.h \
    transaktionsliste.h

FORMS    += haushaltsverwaltung.ui \
    hauptmenue.ui \
    erfassen.ui \
    abrechnung.ui \
    bezahlart.ui \
    benutzerdaten.ui \
    benutzerverwaltung.ui \
    hauptmenue_adm.ui \
    kategorieverwaltung.ui \
    erstanmeldung_adm.ui \
    newpassword.ui \
    transaktionsliste.ui
