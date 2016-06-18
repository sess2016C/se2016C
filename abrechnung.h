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
    void on_btn_AbAbbrechen_clicked();

    void on_cmb_categories_currentIndexChanged(const QString &arg1);

    void on_date_to_dateChanged(const QDate &date);

    void on_date_from_dateChanged(const QDate &date);

private:
    Ui::Abrechnung *ui;
    void updateTable();
    void updateComboBox();
};

#endif // ABRECHNUNG_H
