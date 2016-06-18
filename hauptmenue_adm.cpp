#include "hauptmenue_adm.h"
#include "ui_hauptmenue_adm.h"
#include "haushaltsverwaltung.h"
#include "benutzerverwaltung.h"
#include "kategorieverwaltung.h"
#include "erfassen.h"
#include "abrechnung.h"
#include "bezahlart.h"
#include "benutzerdaten.h"
#include "global.h"
#include <QSqlQuery>

Haushaltsverwaltung *newHaupmenuWindowAdm = 0;
QTableWidget *tableAdm;

hauptmenue_adm::hauptmenue_adm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hauptmenue_adm)
{
    ui->setupUi(this);
    if(!user->isAdmin()) {
        ui->btn_Benutzerverwaltung->setVisible(false);
        ui->btn_Kategorieverwaltung->setVisible(false);
        ui->label_user_im_minus->setVisible(false);
        ui->list_user_im_minus->setVisible(false);
    }
    // Transaktionstabelle
    tableAdm = ui->tbl_Transaktionen;

    tableAdm->horizontalHeader()->setStretchLastSection(true);
    tableAdm->setRowCount(10);
    tableAdm->setColumnCount(6);
    tableAdm->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Datum")));
    tableAdm->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Betrag")));
    tableAdm->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Kategorie")));
    tableAdm->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Quelle")));
    tableAdm->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Zahlungsart")));
    tableAdm->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("")));

    updateTable(10);
}

hauptmenue_adm::~hauptmenue_adm()
{
    delete ui;
}

void hauptmenue_adm::on_btn_Benutzerverwaltung_clicked()
{
    Benutzerverwaltung benutzerverwaltung;
    benutzerverwaltung.setModal(true);
    benutzerverwaltung.exec();
}

void hauptmenue_adm::on_btn_Kategorieverwaltung_clicked()
{
    Kategorieverwaltung kategorieverwaltung;
    kategorieverwaltung.setModal(true);
    kategorieverwaltung.exec();
}

void hauptmenue_adm::on_btn_Abmelden_clicked()
{
    this->hide();
    newHaupmenuWindowAdm = new Haushaltsverwaltung();
    newHaupmenuWindowAdm->show();

}

void hauptmenue_adm::on_btn_Erfassen_clicked()
{
    Erfassen erfassen;
    erfassen.setModal(true);
    erfassen.exec();
    updateTable(10);
}

void hauptmenue_adm::on_btn_Bezahlart_clicked()
{
    Bezahlart bezahlart;
    bezahlart.setModal(true);
    bezahlart.exec();
}

void hauptmenue_adm::on_btn_Benutzerdaten_clicked()
{
    Benutzerdaten benutzerdaten;
    benutzerdaten.setModal(true);
    benutzerdaten.exec();
}

void hauptmenue_adm::updateTable(int rows) {
    tableAdm->clear();

    QSqlQuery query;
    query.prepare("SELECT * FROM Transaktion WHERE bID = (:bid) ORDER BY date(datum) DESC Limit (:lim)");
    query.bindValue(":bid", user->getUID());
    query.bindValue(":lim", QString::number(rows));
    if(query.exec()) {
        int table_row = 0;
        while(query.next()) {
            QString datum = query.value(2).toString();
            datum = convertDate(datum);
            QString betrag = query.value(1).toString();
            qint64 betr = betrag.toLongLong();
            bool einnahme = true;
            if(betr < 0) { einnahme = false; }
            betrag = QString::number(betr / 100) + "," + QString::number(betr / 10 % 10) + QString::number(betr % 10) + "€";
            QString kID = query.value(5).toString();
            QString quelle = query.value(4).toString();
            QString zID = query.value(7).toString();

            //Get Categoryname
            QSqlQuery kid_query;
            kid_query.prepare("SELECT bez FROM Kategorie WHERE kid = (:kid)");
            kid_query.bindValue(":kid", kID);
            kid_query.exec();
            kid_query.next();
            kID = kid_query.value(0).toString();

            //Get Paymentoption
            if(zID != "0") {
                QSqlQuery zid_query;
                zid_query.prepare("SELECT bez FROM Zahlart WHERE zID = (:zid) AND bID = (:bid)");
                zid_query.bindValue(":zid", zID);
                zid_query.bindValue(":bid", user->getUID());
                zid_query.exec();
                zid_query.next();
                zID = zid_query.value(0).toString();
            } else {
                zID = "No Option defined";
            }
            tableAdm->setItem(table_row,0, new QTableWidgetItem(datum));
            tableAdm->setItem(table_row,1, new QTableWidgetItem(betrag));
            //set color for einnahme or ausgabe
            if(einnahme) {
                tableAdm->item(table_row, 1)->setBackgroundColor(Qt::green);
            } else {
                tableAdm->item(table_row, 1)->setBackgroundColor(Qt::red);
            }
            tableAdm->setItem(table_row,2, new QTableWidgetItem(kID));
            tableAdm->setItem(table_row,3, new QTableWidgetItem(quelle));
            tableAdm->setItem(table_row,4, new QTableWidgetItem(zID));
            tableAdm->setCellWidget(table_row, 5, new QPushButton(QString("Details") ));
            table_row++;
        }
    }
}

void hauptmenue_adm::on_btn_Abrechnung_clicked()
{
    Abrechnung abrechnung;
    abrechnung.setModal(true);
    abrechnung.exec();
}

QString hauptmenue_adm::convertDate(QString &date) {
    if(date.contains("-")) {
        QStringList d = date.split("-");
        return d[2] + "." + d[1] + "." + d[0];
    }
    else {
        QStringList d = date.split(".");
        return d[2] + "-" + d[1] + "-" + d[0];
    }
}

int hauptmenue_adm::getTableRowCount(QSqlQuery query) {
    if(query.exec()) {
        int count = 0;
        while(query.next()) {
            count++;
        }
        return count;
    }
    return -1;
}
