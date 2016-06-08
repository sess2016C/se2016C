#ifndef HAUSHALTSVERWALTUNG_H
#define HAUSHALTSVERWALTUNG_H

#include <QMainWindow>

namespace Ui {
class Haushaltsverwaltung;
}

class Haushaltsverwaltung : public QMainWindow
{
    Q_OBJECT

public:
    explicit Haushaltsverwaltung(QWidget *parent = 0);
    ~Haushaltsverwaltung();


private slots:
    void erstanmeldung();
    void newPassword();
    void on_btn_ABeenden_clicked();
    void on_btn_AAnmelden_clicked();

    void on_txt_Passwort_returnPressed();

private:
    Ui::Haushaltsverwaltung *ui;
};

#endif // HAUSHALTSVERWALTUNG_H
