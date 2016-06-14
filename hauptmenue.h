#ifndef HAUPTMENUE_H
#define HAUPTMENUE_H

#include <QMainWindow>

namespace Ui {
class Hauptmenue;
}

class Hauptmenue : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hauptmenue(QWidget *parent = 0);
    ~Hauptmenue();

private slots:
    void on_btn_Abmelden_clicked();

    void on_btn_Erfassen_clicked();

    void on_btn_Abrechnung_clicked();

    void on_btn_Bezahlart_clicked();

    void on_btn_Benutzerdaten_clicked();

    void on_tbl_Transaktionen_activated(const QModelIndex &index);

private:
    Ui::Hauptmenue *ui;
};

#endif // HAUPTMENUE_H
