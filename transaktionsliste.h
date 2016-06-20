#ifndef TRANSAKTIONSLISTE_H
#define TRANSAKTIONSLISTE_H

#include <QDialog>

namespace Ui {
class transaktionsliste;
}

class transaktionsliste : public QDialog
{
    Q_OBJECT

public:
    explicit transaktionsliste(QWidget *parent = 0);
    ~transaktionsliste();

private slots:
    void on_btn_TLAbbrechen_clicked();

    void on_cmb_categories_currentTextChanged(const QString &arg1);

    void handleButton();

private:
    Ui::transaktionsliste *ui;
    void updateComboBox();
    void updateList();
};

#endif // TRANSAKTIONSLISTE_H
