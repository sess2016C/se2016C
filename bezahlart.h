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
    explicit Bezahlart(QWidget *parent = 0);
    ~Bezahlart();

private slots:
    void on_btn_BeAbbrechen_clicked();

    void on_btn_BeHinzufuegen_clicked();

    void on_btn_BeLoeschen_clicked();

private:
    Ui::Bezahlart *ui;
};

#endif // BEZAHLART_H
