#ifndef benutzer_H
#define benutzer_H

#include <QString>
#include "transaktion.h"
#include "kategorie.h"
class benutzer
{
public:
    QList<Transaktion> *transaktionsliste;
    benutzer(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd);
    bool isAdmin();
    int getUID();
    QString getEmail();
    QString getName();
    QString getVname();
    QString getPwd();
    QString getGeb();
    void setGeb(QString &geb);
    void setName(QString &name);
    void setVname(QString &Vname);
    void setPwd(QString &pwd);
    bool anmeldung(QString email, QString passwort);
    void abmeldung();
    Transaktion erfasseTransaktion(qint64 betrag, QString datum, kategorie kat, zahlungsart zahlart, QString quelle, QString beschr);
    bool loescheTransaktion(Transaktion t);
    bool bearbeiteTransaktion(Transaktion t, qint64 betrag, QString datum, kategorie kat, zahlungsart zahlart, QString quelle, QString beschr);
private:
    int uID;
    bool admin;
    QString email;
    QString geb;
    QString name;
    QString vname;
    QString pwd;
};

#endif // benutzer_H
