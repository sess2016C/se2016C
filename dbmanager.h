#include <QString>
#include <QSqlDatabase>
#include <QDebug>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    /**
     * @brief DBManager Öffnet die Datenbank, die im Pfad angegeben wurde.
     * @param path Pfad zur Datenbank.
     */
    DBManager (const QString &path);
    //fuer benutzer und Admin. Bei Operationen des Admin wird nur Attribut in DB geprüft
    //benutzerobjekt und Daten reinschaufeln
    /**
     * @brief connectbenutzer Meldet einen Benutzer am System an. Weißt außerdem der globalen Variablen "benutzer_akt" ihre Werte zu.
     * @param email Email des anzumeldenden Benutzers.
     * @param pw Passwort des anzumeldenden Benutzers.
     * @return
     */
    int connectbenutzer(QString &email, QString &pw);
    /**
     * @brief isOpen Liefert einen Wert, der beschreibt, ob die Datenbank bereit ist.
     * @return True wenn Datenbank bereit, false sonst.
     */
    bool isOpen();
    /**
     * @brief isEmpty Prüft, ob Benutzer in der Datenbank vorhanden sind.
     * @return True, wenn keine Benutzer vorhanden sind, false sonst.
     */
    bool isEmpty(); //keine Benutzer vorhanden
    /**
     * @brief cleanTables Löscht alle Datensätze in der Datenbank.
     * @return True, wenn alles gelöscht wurde, false sonst.
     */
    bool cleanTables();
    /**
     * @brief setupTestData Fügt die geforderten Testdaten in die Datenbank ein.
     */
    void setupTestData();
    //einfach zu loginscreen zurueck?
    /**
     * @brief disconnectbenutzer Trennt einen Benutzer von der Datenbank.
     */
    void disconnectbenutzer();
    /**
     * @brief addCategory Fügt eine Kategorie in die Datenbank ein
     * @param category Name der Kategorie.
     * @return True bei Erfolg, false sonst.
     */
    bool addCategory(QString &category);
    /**
     * @brief resetPW Setzt das Passwort eines Benutzers in der Datenbank zurück.
     * @param email Email des Benutzers, dessen Passwort zurückgesetzt werden soll.
     * @return True bei Erfolg, false sonst.
     */
    bool resetPW(QString &email);
    /**
     * @brief addbenutzer Fügt den Benutzer mit den übergebenen Werten in die Datenbank ein.
     * @return True bei Erfolg, false sonst.
     */
    bool addbenutzer(QString &email, QString &name, QString & vname,QString &geb);
    /**
     * @brief delbenutzer Löscht einen Benutzer aus der Datenbank.
     * @param email Email des Benutzers, der gelöscht wird.
     * @return True bei Erfolg, false sonst.
     */
    bool delbenutzer(QString &email);
    /**
     * @brief delCat Entfernt eine Kategorie aus der Datenbank.
     * @param category Name der zu löschenden Kategorie.
     * @return True bei Erfolg, false sonst.
     */
    bool delCat(QString &category);
    /**
     * @brief getPaymentText Sucht zu einer Zahlungsid die zugehörige Beschreibung.
     * @param tid ID der Zahlungsart.
     * @return  Name der Zahlungsart.
     */
    QString getPaymentText(int tid);
    /**
     * @brief getCategoryText Sucht zu einer Kategorieid die zugehörige Beschreibung.
     * @param kid ID der Kategorie.
     * @return Name der Kategorie.
     */
    QString getCategoryText(int kid);

    //----METHODEN FUER GUI-ANZEIGE----
    //englisch oder deutsch? qulle & zahlart können aber müssen nicht vorhanden sein, evtl. auffuellen mit null
    /**
     * @brief addTransaction Fügt eine Transaktion mit den übergebenen Werten in die Datenbank ein.
     * @return True bei Erfolg, false sonst.
     */
    bool addTransaction(int tID, QString &beschr, qint64 betr, QString &date, QString &quelle, int kID, int bID, int zID);
    /**
     * @brief addPayment Fügt eine Zahlungsart in die Datenbank ein.
     * @param pay Name der Zahlungsart.
     * @param uID Userid des hinzufügenden Benutzers.
     * @return True bei Erfolg, false sonst.
     */
    bool addPayment(QString &pay, int uID);
    /**
     * @brief delPayment Löscht eine Zahlungsart aus der Datenbank.
     * @param pay Name der Zahlungsart.
     * @param uID Userid des löschenden Benutzers.
     * @return True bei Erfolg, false sonst.
     */
    bool delPayment(QString &pay, int uID);
    /**
     * @brief changebenutzerData Ändern die Benutzerdaten des ausführenden Benutzers auf die angegebenen Werte.
     * @return True bei Erfolg, false sonst.
     */
    bool changebenutzerData(QString &name, QString & vname, QString &pwd, QString &geb);
private:
    /**
     * @brief m_db Datenbank.
     */
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
