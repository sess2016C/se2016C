#ifndef benutzer_H
#define benutzer_H

#include <QString>
#include "transaktion.h"
#include "kategorie.h"
class benutzer
{
public:
    /**
     * @brief transaktionsliste Liste, in der alle Transaktionen des Benutzers gespeichert sind.
     */
    QList<Transaktion> *transaktionsliste;
    /**
     * @brief benutzer Konstruktor für ein Benutzerobjekt mit den angebenen Werten.
     */
    benutzer(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd);
    /**
     * @brief isAdmin Prüft, ob der Benutzer ein Administrator ist.
     * @return True, falls Benutzer ein Administrator ist, false sonst.
     */
    bool isAdmin();
    /**
     * @brief getUID Gibt die Benutzerid des Benutzers zurück.
     * @return Benutzerid des Benutzers.
     */
    int getUID();
    /**
     * @brief getEmail Gibt die Email des Benutzers zurück.
     * @return Email des Benutzers.
     */
    QString getEmail();
    /**
     * @brief getName Gibt den Namen des Benutzers zurück.
     * @return Name des Benutzers.
     */
    QString getName();
    /**
     * @brief getVname Gibt den Vornamen des Benutzers zurück.
     * @return Vorname des Benutzers.
     */
    QString getVname();
    /**
     * @brief getPwd Gibt das Passwort des Benutzers zurück.
     * @return Passwort des Benutzers.
     */
    QString getPwd();
    /**
     * @brief getGeb Gibt den Geburtstag des Benutzers zurück.
     * @return Geburtstag des Benutzers.
     */
    QString getGeb();
    /**
     * @brief setGeb Setzt den Geburtstag des Benutzers.
     * @param geb Geburtstag
     */
    void setGeb(QString &geb);
    /**
     * @brief setName Setzt den Namen des Benutzers.
     * @param name Name
     */
    void setName(QString &name);
    /**
     * @brief setVname Setzt den Vornamen des Benutzers.
     * @param Vname Vorname
     */
    void setVname(QString &Vname);
    /**
     * @brief setPwd Setzt das Passwort des Benutzers.
     * @param pwd Passwort
     */
    void setPwd(QString &pwd);
    /**
     * @brief anmeldung Meldet den Benutzer mit "email" und "passwort" am System an.
     * @return  Gibt im Erfolgsfall true, sonst false zurück.
     */
    bool anmeldung(QString email, QString passwort);
    /**
     * @brief abmeldung Meldet den Benutzer am System ab.
     */
    void abmeldung();
    /**
     * @brief erfasseTransaktion Erfasst eine neue Transaktion für den angemeldeten Benutzer mit den angegebenen Parametern
     * @return Gibt die neue Transaktion zurück.
     */
    Transaktion erfasseTransaktion(qint64 betrag, QString datum, kategorie kat, zahlungsart zahlart, QString quelle, QString beschr);
    /**
     * @brief loescheTransaktion Löscht die übergebene Transaktion aus der Liste des Besitzers.
     * @param t Zu löschende Transaktion.
     * @return True im Erfolgsfall, false sonst.
     */
    bool loescheTransaktion(Transaktion t);
    /**
     * @brief bearbeiteTransaktion Updatet Transaktion t mit den übergebenen Werten.
     * @return True im Erfolgsfall, false sonst.
     */
    bool bearbeiteTransaktion(Transaktion t, qint64 betrag, QString datum, kategorie kat, zahlungsart zahlart, QString quelle, QString beschr);
private:
    /**
     * @brief uID Benutzerid des Benutzers.
     */
    int uID;
    /**
     * @brief admin Enthält einen bool, der angibt, ob ein Benutzer ein Administrator ist.
     */
    bool admin;
    /**
     * @brief email Email des Benutzers.
     */
    QString email;
    /**
     * @brief geb Geburtstag des Benutzers.
     */
    QString geb;
    /**
     * @brief name Name des Benutzers.
     */
    QString name;
    /**
     * @brief vname Vorname des Benutzers.
     */
    QString vname;
    /**
     * @brief pwd Passwort des Benutzers.
     */
    QString pwd;
};

#endif // benutzer_H
