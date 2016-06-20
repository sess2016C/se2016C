#ifndef BEZAHLART_H
#define BEZAHLART_H

#include <QDialog>

namespace Ui {
class Bezahlart;
}

class Bezahlart : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Bezahlart Konstruktor der Klasse "Bezahlart".
     * @param parent Standardparameter
     */
    explicit Bezahlart(QWidget *parent = 0);
    /**
     * @brief ~Bezahlart Destruktor der Klasse "Bezahlart".
     */
    ~Bezahlart();

private slots:
    /**
     * @brief on_btn_BeAbbrechen_clicked Button "Abbrechen", welcher den Dialog versteckt.
     */
    void on_btn_BeAbbrechen_clicked();

    /**
     * @brief on_btn_BeHinzufuegen_clicked Button "Hinzufügen", mit dem eine Zahlungsart in die Datenbank hinzugefügt wird.
     */
    void on_btn_BeHinzufuegen_clicked();

    /**
     * @brief on_btn_BeLoeschen_clicked Button "Löschen", mit dem eine Zahlungsart aus der Liste der verfügbaren Zahlungsarten gelöscht wird.
     */
    void on_btn_BeLoeschen_clicked();

    /**
     * @brief updateList Refresht die Liste der verfügbaren Zahlungsarten.
     */
    void updateList();

private:
    Ui::Bezahlart *ui;
};

#endif // BEZAHLART_H
