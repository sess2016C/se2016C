#include "abrechnung.h"
#include "ui_abrechnung.h"
#include "hauptmenue_adm.h"
#include "global.h"
#include "QSqlQuery"
#include <QDebug>
#include <QSqlError>

QTableWidget *abTable;

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

Abrechnung::~Abrechnung()
{
    delete ui;
}

void Abrechnung::on_btn_AbAbbrechen_clicked()
{
    this->hide();
}

void Abrechnung::updateTable() {
    abTable->clear();

    QSqlQuery query;
    if(ui->cmb_categories->currentText() == "-- Alle anzeigen --") {
        query.prepare("SELECT sum(betrag), kid FROM Transaktion WHERE datum >= (:date_from) AND datum <= (:date_to) AND bID = (:bid) GROUP BY kid");
        QString date_from = ui->date_from->text();
        query.bindValue(":date_from", hauptmenue_adm::convertDate(date_from));
        QString date_to = ui->date_to->text();
        query.bindValue(":date_to", hauptmenue_adm::convertDate(date_to));
        query.bindValue(":bid", user->getUID());
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

                abTable->setItem(count, 0, new QTableWidgetItem(kID));
                abTable->setItem(count, 1, new QTableWidgetItem(query.value(0).toString()));
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
            qint64 saldo = 0;
            qDebug() << abTable->rowCount();
            for(int i = 0; i < abTable->rowCount() - 1; i++) {
                saldo += abTable->item(i, 1)->text().toLongLong();
            }
            qDebug() << saldo;
            abTable->setItem(count, 1, new QTableWidgetItem(QString::number(saldo)));
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

        query.prepare("SELECT sum(betrag), kid FROM Transaktion WHERE datum >= (:date_from) AND datum <= (:date_to) AND kID = (:sel_kid) GROUP BY kid");

        QString date_from = ui->date_from->text();
        query.bindValue(":date_from", hauptmenue_adm::convertDate(date_from));
        QString date_to = ui->date_to->text();
        query.bindValue(":date_to", hauptmenue_adm::convertDate(date_to));
        query.bindValue(":sel_kid", catID);
        int row_count = hauptmenue_adm::getTableRowCount(query);
        abTable->setRowCount(2);
        if(query.exec()) {
            int count = 0;
            while(query.next()) {
                abTable->setItem(count, 0, new QTableWidgetItem(ui->cmb_categories->currentText()));
                abTable->setItem(count, 1, new QTableWidgetItem(query.value(0).toString()));
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
            qint64 saldo = 0;
            for(int i = 0; i < abTable->rowCount() - 1; i++) {
                saldo += abTable->item(i, 1)->text().toLongLong();
            }
            abTable->setItem(count, 1, new QTableWidgetItem(QString::number(saldo)));
        }

    }


}

void Abrechnung::updateComboBox() {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    ui->cmb_categories->addItem("-- Alle anzeigen --");
    while(query.next()) {
        ui->cmb_categories->addItem(query.value(0).toString());
    }
}

void Abrechnung::on_cmb_categories_currentIndexChanged(const QString &arg1)
{
    updateTable();
}

void Abrechnung::on_date_to_dateChanged(const QDate &date)
{
    updateTable();
}

void Abrechnung::on_date_from_dateChanged(const QDate &date)
{
    updateTable();
}
