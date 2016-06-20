#ifndef TRANSAKTION_H
#define TRANSAKTION_H
#include "kategorie.h"
#include "zahlungsart.h"
//#include "global.h"
#include <QString>

class Transaktion
{
public:
    Transaktion();
    ~Transaktion();
    QString getDatum();
    QString getBeschreibung();
    qint64 getBetrag();
    kategorie getKategorie();
    QString getQuelle();
    zahlungsart getZahlart();

    bool setDatum(QString date);
    bool setBeschreibung(QString beschr);
    bool setBetrag(qint64 betr);
    bool setKategorie(kategorie kat);
    bool setQuelle(QString quelle);
    bool setZahlungsart(zahlungsart zart);

private:
    int id;
    QString beschreibung;
    int betrag;
    QString datum;
    kategorie kategorie;
    QString quelle;
    QString zahlart;
};

#endif // TRANSAKTION_H
