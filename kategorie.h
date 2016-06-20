#ifndef KATEGORIE_H
#define KATEGORIE_H

#include <QString>

class kategorie
{
public:
    kategorie();
    ~kategorie();
    QString getKategorie();
    bool setKategorie(QString name);
private:
    QString name;
};

#endif // KATEGORIE_H
