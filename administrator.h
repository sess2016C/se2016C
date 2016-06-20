#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "benutzer.h"
/**
 * @brief The administrator class
 *      Eine Unterklasse von "benutzer". Enthält Methoden, die der Admin benötigt.
 */
class administrator : benutzer
{
public:
    /**
     * @brief erstanmeldung Erfasst die Benutzerdaten des Administrators beim ersten Start des Programms
     * @param email Email, über die der Administrator identifiziert werden kann.
     * @param name Name des Administrators.
     * @param nachname Nachname des Administrators.
     * @param passwort Passwort des Administrators (Standardmäßig 0000).
     * @param geburtsdatum Geburtsdatum des Administrators.
     */
    void erstanmeldung(QString email, QString name, QString nachname, QString passwort, QString geburtsdatum);
    /**
     * @brief getNegativeKonten Listet Benutzer mit negativem Gesamtsaldo auf.
     * @return Liste der Benutzer mit negativem Gesamtsaldo.
     */
    QList<benutzer> getNegativeKonten();
    /**
     * @brief setzePasswortZurueck Setzt das Passwort eines Benutzers mit der Email "email" zurück.
     * @param email Emails des Benutzers, dessen Passwort zurückgesetzt wird.
     * @return True im Erfolgfall, false sonst.
     */
    bool setzePasswortZurueck(QString email);
};

#endif // ADMINISTRATOR_H
