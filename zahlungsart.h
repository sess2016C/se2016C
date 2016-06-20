#ifndef ZAHLUNGSART_H
#define ZAHLUNGSART_H

#include <QString>

class zahlungsart
{
public:
    zahlungsart();
    ~zahlungsart();
    QString getZahlungsart();
    bool setZahlungsart(QString zahlart);

private:
    QString zahlart;
};

#endif // ZAHLUNGSART_H
