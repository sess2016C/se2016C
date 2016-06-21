#ifndef TRANSAKTIONSLISTE_H
#define TRANSAKTIONSLISTE_H

#include <QDialog>

namespace Ui {
class transaktionsliste;
}

/**
 * @brief The transaktionsliste class Die Klasse für die Anzeige der Transaktionen.
 */
class transaktionsliste : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief transaktionsliste Konstruktor der Klasse Transaktionsliste.
     * @param parent Standartparameter
     */
    explicit transaktionsliste(QWidget *parent = 0);
    /**
     * @brief ~transaktionsliste Destruktor der Klasse Transaktionsliste
     */
    ~transaktionsliste();

private slots:
    /**
     * @brief on_btn_TLAbbrechen_clicked Slot des Buttons "Abbrechen", der das Fenster der Klasse Transaktionsliste schließt.
     */
    void on_btn_TLAbbrechen_clicked();

    /**
     * @brief on_cmb_categories_currentTextChanged Slot, der aufgerufen wird, wenn sich der Text in der Combobox ändert.
     * @param arg1 Standardparameter.
     */
    void on_cmb_categories_currentTextChanged(const QString &arg1);

    /**
     * @brief handleButton Slot der dynamisch generierten "Details"-Buttons, welcher das Detailansichtfenster aufruft.
     */
    void handleButton();

private:
    Ui::transaktionsliste *ui;
    /**
     * @brief updateComboBox Methode, die die Kategorien und ein zusätzliches Item "-- Alles anzeigen --" enthält.
     */
    void updateComboBox();
    /**
     * @brief updateList Zeigt die Transaktionen des aktuellen Benutzers aus der Datenbank in der Liste an.
     */
    void updateList();
};

#endif // TRANSAKTIONSLISTE_H
