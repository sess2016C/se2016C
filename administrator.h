#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "benutzer.h"
class administrator : benutzer
{
public:
    void erstanmeldung(QString email, QString name, QString nachname, QString passwort, QString geburtsdatum);
    QList<benutzer> getNegativeKonten();
    bool setzePasswortZurueck(QString email);
};

#endif // ADMINISTRATOR_H
