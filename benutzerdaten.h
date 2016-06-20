#ifndef BENUTZERDATEN_H
#define BENUTZERDATEN_H

#include <QDialog>

namespace Ui {
class Benutzerdaten;
}

class Benutzerdaten : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Benutzerdaten Konstruktor für die Benutzeroberfläche des Dialogs "Benutzerdaten ändern",
     * in dem der Benutzer seine persönlichen Daten abrufen und ändern kann.
     * @param parent Standardparameter
     */
    explicit Benutzerdaten(QWidget *parent = 0);
    /**
     * @brief ~Benutzerdaten Destruktor der Klasse "Benutzerdaten".
     */
    ~Benutzerdaten();

private slots:
    /**
     * @brief on_btn_NuAbbrechen_clicked Slot des Buttons "Abbrechen".
     */
    void on_btn_NuAbbrechen_clicked();
    /**
     * @brief on_btn_NuSpeichern_clicked Slot des Buttons "Speichern". Hier werden die Daten übernommen, welche der
     * Benutzer eingetragen hat.
     */
    void on_btn_NuSpeichern_clicked();

private:
    Ui::Benutzerdaten *ui;
};

#endif // BENUTZERDATEN_H
