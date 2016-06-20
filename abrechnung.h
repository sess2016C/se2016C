#ifndef ABRECHNUNG_H
#define ABRECHNUNG_H

#include <QDialog>

namespace Ui {
class Abrechnung;
}

class Abrechnung : public QDialog
{
    Q_OBJECT

public:
    explicit Abrechnung(QWidget *parent = 0);
    ~Abrechnung();



private slots:
    /**
     * @brief on_btn_AbAbbrechen_clicked Slot des Buttons "Abbrechen"
     */
    void on_btn_AbAbbrechen_clicked();
    /**
     * @brief on_cmb_categories_currentIndexChanged Slot der Combobox, in der die Kategorien angezeigt werden.
     * @param arg1 Standardargument
     */
    void on_cmb_categories_currentIndexChanged(const QString &arg1);

    /**
     * @brief on_date_to_dateChanged Slot des Datumsfelds, in dem das Enddatum angezeigt wird.
     * @param date Standardargument
     */
    void on_date_to_dateChanged(const QDate &date);

    /**
     * @brief on_date_from_dateChanged Slot des Datumsfelds, in dem das Startdatum angezeigt wird.
     * @param date Standardargument
     */
    void on_date_from_dateChanged(const QDate &date);

private:
    Ui::Abrechnung *ui;
    /**
     * @brief updateTable Refresht die Tabelle mit den Abrechnungen.
     */
    void updateTable();

    /**
     * @brief updateComboBox Stellt die Kategorien des Programms in der Combobox dar.
     */
    void updateComboBox();
};

#endif // ABRECHNUNG_H
