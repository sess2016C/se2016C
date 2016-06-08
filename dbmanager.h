#include <QString>
#include <QSqlDatabase>
#include <QDebug>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager (const QString &path);
    //fuer User und Admin. Bei Operationen des Admin wird nur Attribut in DB geprüft
    //Userobjekt und Daten reinschaufeln
    int connectUser(QString &email, QString &pw);
    bool isOpen();
    bool isEmpty(); //keine Benutzer vorhanden
    //einfach zu loginscreen zurueck?
    void disconnectUser();
    bool addCategory(QString &category);
    bool resetPW(QString &email);
    bool addUser(QString &email, QString &name, QString & vname,QString &geb, QString &stdpw);
    bool delUser(QString &email);
    bool delCat(QString &category);

    //----METHODEN FUER GUI-ANZEIGE----
    //englisch oder deutsch? qulle & zahlart können aber müssen nicht vorhanden sein, evtl. auffuellen mit null
    bool addTransaction(int tID, QString &beschr, int betr, QString &date, QString &quelle, int kID, int bID, int zID);
    bool showAccount();
    void editPaymentOptions();
    bool editTransaction(); //Uebergabewert? Oder hat Benutzer alle Transaktionen als Objekte und editTransaktion usw. kann als Objektmethode implementiert werden?
    bool changeUserData(QString &name, QString & vname, QString &pwd, QString &geb);
    bool deleteTransaction(); //s.o.
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
