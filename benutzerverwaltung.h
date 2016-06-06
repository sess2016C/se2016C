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
    explicit Benutzerverwaltung(QWidget *parent = 0);
    ~Benutzerverwaltung();

private slots:
    void on_btn_BvAbbrechen_clicked();

private:
    Ui::Benutzerverwaltung *ui;
};

#endif // BENUTZERVERWALTUNG_H
