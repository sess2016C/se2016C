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

    for( int i = 0; i < tableAdm->rowCount(); i++ ){
        tableAdm->setCellWidget( i, 5, new QPushButton(QString("Details") ));
    }
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
    QSqlQuery query;
    int count = 0;
    query.prepare("SELECT * FROM Transaktion WHERE bID = (:bid)");
    query.bindValue(":bid", user->getUID());
    if(query.exec()) {
        while(query.next() && count < rows) {
            QString datum = query.value(2).toString();
            QString betrag = query.value(1).toString();
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
            qDebug() << kID;

            //Get Paymentoption
            if(zID != "0") {
                QSqlQuery zid_query;
                zid_query.prepare("SELECT bez FROM Zahlart WHERE zID = (:zid) AND bID = (:bid)");
                zid_query.bindValue(":zid", zID);
                zid_query.bindValue(":bid", user->getUID());
                zid_query.exec();
                zid_query.next();
                zID = zid_query.value(0).toString();
                qDebug() << zID;
            } else {
                zID = "No Option defined";
            }
            tableAdm->setItem(count,0, new QTableWidgetItem(datum));
            tableAdm->setItem(count,1, new QTableWidgetItem(betrag));
            tableAdm->setItem(count,2, new QTableWidgetItem(kID));
            tableAdm->setItem(count,3, new QTableWidgetItem(quelle));
            tableAdm->setItem(count,4, new QTableWidgetItem(zID));
            count++;
        }
    }
}
