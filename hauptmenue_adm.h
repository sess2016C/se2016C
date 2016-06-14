#ifndef HAUPTMENUE_ADM_H
#define HAUPTMENUE_ADM_H

#include <QMainWindow>

namespace Ui {
class hauptmenue_adm;
}

class hauptmenue_adm : public QMainWindow
{
    Q_OBJECT

public:
    explicit hauptmenue_adm(QWidget *parent = 0);
    ~hauptmenue_adm();

private slots:
    void on_btn_Benutzerverwaltung_clicked();

    void on_btn_Kategorieverwaltung_clicked();

    void on_btn_Abmelden_clicked();

    void on_btn_Erfassen_clicked();

    void on_btn_Bezahlart_clicked();

    void on_btn_Benutzerdaten_clicked();

private:
    Ui::hauptmenue_adm *ui;
};

#endif // HAUPTMENUE_ADM_H
