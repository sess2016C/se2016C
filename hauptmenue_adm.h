#ifndef HAUPTMENUE_ADM_H
#define HAUPTMENUE_ADM_H

#include <QMainWindow>
#include <QSqlQuery>

namespace Ui {
class hauptmenue_adm;
}

/**
 * @brief The hauptmenue_adm class
 * Header-Datei für die Klasse "hauptmenue_adm".
 */
class hauptmenue_adm : public QMainWindow
{
    Q_OBJECT

public:
    explicit hauptmenue_adm(QWidget *parent = 0);
    ~hauptmenue_adm();
    static QString convertDate(QString &date);
    static int getTableRowCount(QSqlQuery query);
    static qint64 getSaldo(int benutzerID);
    static QString convertNumberToSaldo(qint64 number);

private slots:
    void on_btn_Benutzerverwaltung_clicked();

    void on_btn_Kategorieverwaltung_clicked();

    void on_btn_Abmelden_clicked();

    void on_btn_Erfassen_clicked();

    void on_btn_Bezahlart_clicked();

    void on_btn_Benutzerdaten_clicked();

    void on_btn_Abrechnung_clicked();

    void handleButton();

    void on_btn_transaktionsliste_clicked();

private:
    Ui::hauptmenue_adm *ui;
    void updateTable(int rows);

};

#endif // HAUPTMENUE_ADM_H
