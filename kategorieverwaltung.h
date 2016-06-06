#ifndef KATEGORIEVERWALTUNG_H
#define KATEGORIEVERWALTUNG_H

#include <QDialog>

namespace Ui {
class Kategorieverwaltung;
}

class Kategorieverwaltung : public QDialog
{
    Q_OBJECT

public:
    explicit Kategorieverwaltung(QWidget *parent = 0);
    ~Kategorieverwaltung();

private slots:
    void on_btn_KvAbbrechen_clicked();

private:
    Ui::Kategorieverwaltung *ui;
};

#endif // KATEGORIEVERWALTUNG_H
