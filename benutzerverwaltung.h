#ifndef BENUTZERVERWALTUNG_H
#define BENUTZERVERWALTUNG_H

#include <QDialog>

namespace Ui {
class Benutzerverwaltung;
}

class Benutzerverwaltung : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Benutzerverwaltung Konstruktor der Klasse "Benutzerverwaltung", welche den Administrator die Benutzer
     * verwalten lässt.
     * @param parent Standardparameter.
     */
    explicit Benutzerverwaltung(QWidget *parent = 0);
    /**
     * @brief ~Benutzerverwaltung Destruktor der Klasse "Benutzerverwaltung".
     */
    ~Benutzerverwaltung();

private slots:
    /**
     * @brief on_btn_BvAbbrechen_clicked Slot des Buttons "Abbrechen", welcher das Fenster verschwinden lässt.
     */
    void on_btn_BvAbbrechen_clicked();

    /**
     * @brief on_btn_benutzerAnlegen_clicked Button, welcher bei einem Klick darauf einen neuen Benutzer mit den
     * in der GUI angegebenen Werten anlegt.
     */
    void on_btn_benutzerAnlegen_clicked();

    /**
     * @brief on_btn_benutzerDel_clicked Löscht einen Benutzer.
     */
    void on_btn_benutzerDel_clicked();

    /**
     * @brief on_btn_benutzerResetPW_clicked Setzt das Passwort eines Benutzers zurück.
     */
    void on_btn_benutzerResetPW_clicked();

private:
    Ui::Benutzerverwaltung *ui;
    /**
     * @brief updateTable Zeigt die vorhandenen Benutzer (außer den Administrator) in eiener Liste an.
     */
    void updateTable();
};

#endif // BENUTZERVERWALTUNG_H
