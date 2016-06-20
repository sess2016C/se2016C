#ifndef ERSTANMELDUNG_ADM_H
#define ERSTANMELDUNG_ADM_H

#include <QDialog>

namespace Ui {
class Erstanmeldung_adm;
}

/**
 * @brief The Erstanmeldung_adm class
 * Header-Datei für die Klasse "erstanmeldung_adm".
 */
class Erstanmeldung_adm : public QDialog
{
    Q_OBJECT

public:
    explicit Erstanmeldung_adm(QWidget *parent = 0);
    ~Erstanmeldung_adm();

private slots:
    void on_btn_EaBeenden_clicked();

    void on_btn_EaAnlegen_clicked();

private:
    Ui::Erstanmeldung_adm *ui;
};

#endif // ERSTANMELDUNG_ADM_H
