#include <QString>
#include <QSqlDatabase>
#include <QDebug>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager (const QString &path);
    //fuer benutzer und Admin. Bei Operationen des Admin wird nur Attribut in DB geprüft
    //benutzerobjekt und Daten reinschaufeln
    int connectbenutzer(QString &email, QString &pw);
    bool isOpen();
    bool isEmpty(); //keine Benutzer vorhanden
    //einfach zu loginscreen zurueck?
    void disconnectbenutzer();
    bool addCategory(QString &category);
    bool resetPW(QString &email);
    bool addbenutzer(QString &email, QString &name, QString & vname,QString &geb);
    bool delbenutzer(QString &email);
    bool delCat(QString &category);
    QString getPaymentText(int tid);
    QString getCategoryText(int kid);

    //----METHODEN FUER GUI-ANZEIGE----
    //englisch oder deutsch? qulle & zahlart können aber müssen nicht vorhanden sein, evtl. auffuellen mit null
    bool addTransaction(int tID, QString &beschr, qint64 betr, QString &date, QString &quelle, int kID, int bID, int zID);
    bool showAccount();
    bool addPayment(QString &pay, int uID);
    bool delPayment(QString &pay, int uID);
    bool editTransaction(); //Uebergabewert? Oder hat Benutzer alle Transaktionen als Objekte und editTransaktion usw. kann als Objektmethode implementiert werden?
    bool changebenutzerData(QString &name, QString & vname, QString &pwd, QString &geb);
    bool deleteTransaction(); //s.o.
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
