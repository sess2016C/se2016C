#ifndef KATEGORIEVERWALTUNG_H
#define KATEGORIEVERWALTUNG_H

#include <QDialog>

namespace Ui {
class Kategorieverwaltung;
}

/**
 * @brief The Kategorieverwaltung class
 * Header-Datei der Klasse "Kategorieverwaltung".
 */
class Kategorieverwaltung : public QDialog
{
    Q_OBJECT

public:
    explicit Kategorieverwaltung(QWidget *parent = 0);
    ~Kategorieverwaltung();

private slots:
    void on_btn_KvAbbrechen_clicked();

    void on_btn_BeHinzufuegen_clicked();

    void on_btn_BeLoeschen_clicked();

private:
    Ui::Kategorieverwaltung *ui;
    void updateList();
};

#endif // KATEGORIEVERWALTUNG_H
