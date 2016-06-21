#include "benutzer.h"
#include "qdebug.h"

/**
 * @brief benutzer_akt Zeiger auf das Objekt, welches den angemeldeten Benutzer enthält.
 */
benutzer *benutzer_akt;

/**
 * @brief benutzer Konstruktor für ein Benutzerobjekt mit den angebenen Werten.
 */
benutzer::benutzer(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd) {
    this->uID = uID;
    this->admin = admin;
    this->email = email;
    this->geb = geb;
    this->name = name;
    this->vname = vname;
    this->pwd = pwd;
}
/**
 * @brief isAdmin Prüft, ob der Benutzer ein Administrator ist.
 * @return True, falls Benutzer ein Administrator ist, false sonst.
 */
bool benutzer::isAdmin(){ return admin; }

/**
 * @brief getUID Gibt die Benutzerid des Benutzers zurück.
 * @return Benutzerid des Benutzers.
 */
int benutzer::getUID() { return uID; }

/**
 * @brief getEmail Gibt die Email des Benutzers zurück.
 * @return Email des Benutzers.
 */
QString benutzer::getEmail() { return email; }

/**
 * @brief getName Gibt den Namen des Benutzers zurück.
 * @return Name des Benutzers.
 */
QString benutzer::getGeb() { return geb; }

/**
 * @brief getVname Gibt den Namen des Benutzers zurück.
 * @return Name des Benutzers.
 */
QString benutzer::getName() { return name; }

/**
 * @brief getVname Gibt den Vornamen des Benutzers zurück.
 * @return Vorname des Benutzers.
 */
QString benutzer::getVname() { return vname; }

/**
 * @brief getPwd Gibt das Passwort des Benutzers zurück.
 * @return Passwort des Benutzers.
 */
QString benutzer::getPwd() { return pwd; }

/**
 * @brief setGeb Setzt den Geburtstag des Benutzers.
 * @param geb Geburtstag
 */
void benutzer::setGeb(QString &geb) { this->geb = geb; }
/**
 * @brief setName Setzt den Namen des Benutzers.
 * @param name Name
 */
void benutzer::setName(QString &name) { this->name = name; }

/**
 * @brief setVname Setzt den Vornamen des Benutzers.
 * @param Vname Vorname
 */
void benutzer::setVname(QString &Vname) { this->vname = Vname; }
/**
 * @brief setPwd Setzt das Passwort des Benutzers.
 * @param pwd Passwort
 */
void benutzer::setPwd(QString &pwd) { this->pwd = pwd; }
