#include "abrechnung.h"
#include "ui_abrechnung.h"
#include "hauptmenue_adm.h"
#include "global.h"
#include "QSqlQuery"
#include <QDebug>
#include <QSqlError>

/**
 * @brief abTable Zeiger auf die Tabelle, welche die Abrechnung enthält.
 */
QTableWidget *abTable;

/**
 * @brief Abrechnung::Abrechnung
 * Erstellt das Abrechnungsfenster und initialisiert die Tabelle, in denen die Abrechnung und das Gesamtsalod angezeigt werden.
 * @param parent Standardparameter
 */
Abrechnung::Abrechnung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Abrechnung)
{
    ui->setupUi(this);

    abTable = ui->tbl_AbTable;

    abTable->horizontalHeader()->setStretchLastSection(true);
    //abTable->setRowCount(1);
    abTable->setColumnCount(2);
    abTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Kategorie")));
    abTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Saldo")));

    updateComboBox();
    updateTable();

}

/**
 * @brief Abrechnung::~Abrechnung Destruktor für Abrechnung
 */
Abrechnung::~Abrechnung()
{
    delete ui;
}

/**
 * @brief Abrechnung::on_btn_AbAbbrechen_clicked
 * Slot des Abbrechen-Buttons der Klasse Abrechnung. Versteckt den aufgerufenen Dialog.
 */
void Abrechnung::on_btn_AbAbbrechen_clicked()
{
    this->hide();
}

/**
 * @brief Abrechnung::updateTable
 * Löscht den Inhalt der Tabelle. Dann wird die Tabelle neu aufgebaut
 * und neu befüllt. Eine Unterscheidung nach Kategorien kann getroffen werden.
 */
void Abrechnung::updateTable() {
    abTable->clear();

    abTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Bezeichnung")));
    abTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Saldo")));

    QSqlQuery query;
    if(ui->cmb_categories->currentText() == "-- Alle anzeigen --") {
        query.prepare("SELECT sum(betrag), kid FROM Transaktion WHERE datum >= (:date_from) AND datum <= (:date_to) AND bID = (:bid) GROUP BY kid");
        QString date_from = ui->date_from->text();
        query.bindValue(":date_from", hauptmenue_adm::convertDate(date_from));
        QString date_to = ui->date_to->text();
        query.bindValue(":date_to", hauptmenue_adm::convertDate(date_to));
        query.bindValue(":bid", benutzer_akt->getUID());
        int row_count = hauptmenue_adm::getTableRowCount(query);
        abTable->setRowCount(row_count + 1);
        if(query.exec()) {
            int count = 0;
            while(query.next()) {
                QString kID = query.value(1).toString();
                //Get Categoryname
                QSqlQuery kid_query;
                kid_query.prepare("SELECT bez FROM Kategorie WHERE kid = (:kid)");
                kid_query.bindValue(":kid", kID);
                kid_query.exec();
                kid_query.next();
                kID = kid_query.value(0).toString();

                abTable->setItem(count, 0, new QTableWidgetItem(kID)); //set category name
                abTable->setItem(count, 1, new QTableWidgetItem(hauptmenue_adm::convertNumberToSaldo(query.value(0).toLongLong()))); //set category saldo
                if(query.value(0).toLongLong() >= 0) {
                    abTable->item(count, 1)->setBackgroundColor(Qt::green);
                }
                else {
                    abTable->item(count, 1)->setBackgroundColor(Qt::red);
                }

                count++;
            }
            //add gesamt
            abTable->setItem(count, 0, new QTableWidgetItem("Gesamt: "));

            query.prepare("SELECT sum(betrag) FROM Transaktion WHERE bid = (:bid)");
            query.bindValue(":bid", benutzer_akt->getUID());
            query.exec();
            query.next();
            qint64 saldo = query.value(0).toLongLong();
            QString saldo_txt = hauptmenue_adm::convertNumberToSaldo(saldo);
            abTable->setItem(count, 1, new QTableWidgetItem(saldo_txt));
        }
        else {
            qDebug() << query.lastError();
        }

    }
    else {
        //get category id
        int catID;
        query.prepare("SELECT kID FROM Kategorie WHERE bez = (:bez)");
        query.bindValue(":bez", ui->cmb_categories->currentText());
        if(query.exec()) {
            if(query.next()) {
                catID = query.value(0).toInt();
            }
        }

        query.prepare("SELECT sum(betrag), kid FROM Transaktion WHERE datum >= (:date_from) AND datum <= (:date_to) AND kID = (:sel_kid) AND bid = (:bid) GROUP BY kid");

        QString date_from = ui->date_from->text();
        query.bindValue(":date_from", hauptmenue_adm::convertDate(date_from));
        QString date_to = ui->date_to->text();
        query.bindValue(":date_to", hauptmenue_adm::convertDate(date_to));
        query.bindValue(":sel_kid", catID);
        query.bindValue(":bid", benutzer_akt->getUID());
        abTable->setRowCount(2); //kategorie und gesamt
        if(query.exec()) {
            if(query.next()) {
                abTable->setItem(0, 0, new QTableWidgetItem(ui->cmb_categories->currentText())); //category name
                abTable->setItem(0, 1, new QTableWidgetItem(hauptmenue_adm::convertNumberToSaldo(query.value(0).toLongLong()))); //saldo
                if(query.value(0).toLongLong() >= 0) {
                    abTable->item(0, 1)->setBackgroundColor(Qt::green);
                }
                else {
                    abTable->item(0, 1)->setBackgroundColor(Qt::red);
                }
                //add gesamt
                abTable->setItem(1, 0, new QTableWidgetItem("Gesamt: "));
                query.prepare("SELECT sum(betrag) FROM Transaktion WHERE bid = (:bid) AND kid = (:catid)");
                query.bindValue(":bid", benutzer_akt->getUID());
                query.bindValue(":catid", catID);
                query.exec();
                query.next();
                qDebug() << query.value(0).toLongLong();
                abTable->setItem(1, 1, new QTableWidgetItem(hauptmenue_adm::convertNumberToSaldo(query.value(0).toLongLong())));
            } else {
                abTable->setRowCount(0);
            }

        }

    }


}

/**
 * @brief Abrechnung::updateComboBox Aktualisiert die Combobox mit den in der Datenbank erhaltenen Kategorien und fügt zusätzlich eine Auswahlmöglichkeit
 * "-- Alle anzeigen --" hinzu, die eine Abrechnung für alle Kategorien erstellt.
 */
void Abrechnung::updateComboBox() {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    ui->cmb_categories->addItem("-- Alle anzeigen --");
    while(query.next()) {
        ui->cmb_categories->addItem(query.value(0).toString());
    }
}

/**
 * @brief Abrechnung::on_cmb_categories_currentIndexChanged Refresht die Tabelle, wenn sich die ausgewählte Kategorie geändert hat.
 * @param arg1 Standardargument
 */
void Abrechnung::on_cmb_categories_currentIndexChanged(const QString &arg1)
{
    updateTable();
}

/**
 * @brief Abrechnung::on_date_to_dateChanged Refresht die Tabelle, wenn sich das ausgewählte Startdatum geändert hat.
 * @param date Standardargument
 */
void Abrechnung::on_date_to_dateChanged(const QDate &date)
{
    updateTable();
}

/**
 * @brief Abrechnung::on_date_from_dateChanged Refresht die Tabelle, wenn sich das ausgewählte Enddatum geändert hat.
 * @param date Standardargument
 */
void Abrechnung::on_date_from_dateChanged(const QDate &date)
{
    updateTable();
}
