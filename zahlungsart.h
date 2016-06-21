#ifndef ZAHLUNGSART_H
#define ZAHLUNGSART_H

#include <QString>

class zahlungsart
{
public:
    /**
     * @brief zahlungsart Konstruktor der Klasse "zahlungsart".
     */
    zahlungsart();
    /**
     * @brief ~zahlungsart Destruktor der Klasse "zahlungsart".
     */
    ~zahlungsart();
    /**
     * @brief getZahlungsart Gibt den Namen der Zahlungsart zurück.
     * @return Name der Zahlungsart.
     */
    QString getZahlungsart();
    /**
     * @brief setZahlungsart Setzt die Zahlungsart eines "zahlungsart"-Objekts.
     * @param zahlart Zu setzende Zahlungsart.
     * @return True im Erfolgsfall, false sonst.
     */
    bool setZahlungsart(QString zahlart);

private:
    /**
     * @brief zahlart Name der Zahlungsart.
     */
    QString zahlart;
};

#endif // ZAHLUNGSART_H
