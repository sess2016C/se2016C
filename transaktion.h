#ifndef TRANSAKTION_H
#define TRANSAKTION_H
#include "kategorie.h"
#include "zahlungsart.h"
//#include "global.h"
#include <QString>

/**
 * @brief The Transaktion class
 * Transaktionsklasse, die Objekte vom Typ Transaktion bereitstellt.
 */
class Transaktion
{
public:
    /**
     * @brief Transaktion
     * Konstruktor der Klasse Transaktion.
     */
    Transaktion();
    /**
     * @brief ~Transaktion Destruktor der Klasse Transaktion.
     */
    ~Transaktion();
    /**
     * @brief getDatum Gibt das Datum einer Transaktion zurück.
     * @return Datum der Transaktion.
     */
    QString getDatum();
    /**
     * @brief getBeschreibung Gibt die Beschreibung einer Transaktion zurück.
     * @return Beschreibung der Transaktion.
     */
    QString getBeschreibung();
    /**
     * @brief getBetrag Gibt den Betrag einer Transaktion zurück.
     * @return Betrag der Transaktion.
     */
    qint64 getBetrag();
    /**
     * @brief getKategorie Gibt die Kategorie einer Transaktion zurück.
     * @return Kategorie der Transaktion.
     */
    kategorie getKategorie();
    /**
     * @brief getQuelle Gibt die Quelle einer Transaktion zurück.
     * @return Quelle der Transaktion.
     */
    QString getQuelle();
    /**
     * @brief getZahlart Gibt die Zahlart einer Transaktion zurück.
     * @return Zahlart der Transaktion
     */
    zahlungsart getZahlart();

    /**
     * @brief setDatum Setzt das Datum einer Transaktion.
     * @param date Zu setzendes Datum.
     * @return
     */
    bool setDatum(QString date);
    /**
     * @brief setBeschreibung Setzt die Beschreibung einer Transaktion.
     * @param beschr Zu setzende Beschreibung.
     * @return
     */
    bool setBeschreibung(QString beschr);
    /**
     * @brief setBetrag Setzt den Betrag einer Transaktion.
     * @param betr Zu setzender Betrag
     * @return
     */
    bool setBetrag(qint64 betr);
    /**
     * @brief setKategorie Setzt die Kategorie einer Transaktion.
     * @param kat Zu setzende Kategorie.
     * @return
     */
    bool setKategorie(kategorie kat);
    /**
     * @brief setQuelle Setzt die Quelle einer Transaktion.
     * @param quelle Zu setzende Quelle.
     * @return
     */
    bool setQuelle(QString quelle);
    /**
     * @brief setZahlungsart Setzt die Zahlungsart einer Transaktion.
     * @param zart Zu setzende Zahlungsart.
     * @return
     */
    bool setZahlungsart(zahlungsart zart);

private:
    /**
     * @brief id ID der Transaktion.
     */
    int id;
    /**
     * @brief beschreibung Beschreibung der Transaktion.
     */
    QString beschreibung;
    /**
     * @brief betrag Betrag der Transaktion.
     */
    int betrag;
    /**
     * @brief datum Datum der Transaktion.
     */
    QString datum;
    /**
     * @brief kategorie Kategorie der Transaktion.
     */
    kategorie kategorie;
    /**
     * @brief quelle Quelle der Transaktion.
     */
    QString quelle;
    /**
     * @brief zahlart Zahlungsart der Transaktion.
     */
    QString zahlart;
};

#endif // TRANSAKTION_H
