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

private:
    Ui::Abrechnung *ui;
};

#endif // ABRECHNUNG_H
