#ifndef BENUTZERDATEN_H
#define BENUTZERDATEN_H

#include <QDialog>

namespace Ui {
class Benutzerdaten;
}

class Benutzerdaten : public QDialog
{
    Q_OBJECT

public:
    explicit Benutzerdaten(QWidget *parent = 0);
    ~Benutzerdaten();

private slots:
    void on_btn_NuAbbrechen_clicked();

    void on_btn_NuSpeichern_clicked();

private:
    Ui::Benutzerdaten *ui;
};

#endif // BENUTZERDATEN_H
