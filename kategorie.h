#ifndef KATEGORIE_H
#define KATEGORIE_H

#include <QString>

/**
 * @brief The kategorie class
 * Header-Datei für die Klasse "Kategorie".
 */
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
