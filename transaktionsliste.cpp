#include "transaktionsliste.h"
#include "ui_transaktionsliste.h"
#include "global.h"
#include "hauptmenue_adm.h"
#include "erfassen.h"
#include <QSqlQuery>

QList <int> *TStransaktionen; //hier werden transaktionsids der angezeigten transaktionen gespeichert
QTableWidget *tableTL;

transaktionsliste::transaktionsliste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transaktionsliste)
{
    ui->setupUi(this);
    tableTL = ui->tbl_TLTable;
    updateComboBox();
    updateList();
}

transaktionsliste::~transaktionsliste()
{
    delete ui;
}

void transaktionsliste::on_btn_TLAbbrechen_clicked()
{
    this->hide();
}

void transaktionsliste::on_cmb_categories_currentTextChanged(const QString &arg1)
{
    updateList();
}

void transaktionsliste::updateComboBox() {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    ui->cmb_categories->addItem("-- Alle anzeigen --");
    while(query.next()) {
        ui->cmb_categories->addItem(query.value(0).toString());
    }

}

void transaktionsliste::updateList() {
    tableTL->clear();
    tableTL->setColumnCount(6);
    tableTL->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Datum")));
    tableTL->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Betrag")));
    tableTL->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Kategorie")));
    tableTL->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Quelle")));
    tableTL->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Zahlungsart")));
    tableTL->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("")));

    QSqlQuery query;
    if(ui->cmb_categories->currentText() == "-- Alle anzeigen --") {
        query.prepare("SELECT * FROM Transaktion WHERE bid = (:bid)");
    } else {
        //get category id
        int catID;
        query.prepare("SELECT kID FROM Kategorie WHERE bez = (:bez)");
        query.bindValue(":bez", ui->cmb_categories->currentText());
        if(query.exec()) {
            if(query.next()) {
                catID = query.value(0).toInt();
            }
        }
        query.prepare("SELECT * FROM Transaktion WHERE bid = (:bid) and kid = (:kid)");
        query.bindValue(":kid", catID);
    }

    query.bindValue(":bid", benutzer_akt->getUID());
    int count = 0;
    if(query.exec()) {
        while(query.next()) {
            count++;
        }
    }
    tableTL->setRowCount(count);
    if(query.exec()) {
        int table_row = 0;
        TStransaktionen = new QList<int>;
        while(query.next()) {
            //get some stuff from query
            TStransaktionen->append(query.value(0).toInt());
            QString datum = query.value(2).toString();
            datum = hauptmenue_adm::convertDate(datum);
            QString betrag = query.value(1).toString();
            qint64 betr = betrag.toLongLong();
            bool einnahme = true;
            if(betr < 0) { einnahme = false; }
            betrag = hauptmenue_adm::convertNumberToSaldo(betr);
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
                zid_query.bindValue(":bid", benutzer_akt->getUID());
                zid_query.exec();
                zid_query.next();
                zID = zid_query.value(0).toString();
            } else {
                zID = "";
            }
            tableTL->setItem(table_row,0, new QTableWidgetItem(datum));
            tableTL->setItem(table_row,1, new QTableWidgetItem(betrag));
            //set color for einnahme or ausgabe
            if(einnahme) {
                //tableTL->item(table_row, 1)->setBackgroundColor(Qt::green);
            } else {
                //tableTL->item(table_row, 1)->setBackgroundColor(Qt::red);
            }
            tableTL->setItem(table_row,2, new QTableWidgetItem(kID));
            tableTL->setItem(table_row,3, new QTableWidgetItem(quelle));
            tableTL->setItem(table_row,4, new QTableWidgetItem(zID));
            QPushButton *btn = new QPushButton("Details");
            btn->setObjectName(QString::number(table_row));
            tableTL->setCellWidget(table_row, 5, btn ); //how to programm these buttons
            connect(btn, SIGNAL (released()), this, SLOT (handleButton()));
            table_row++;
        }
    } else {
        exit(2);
    }

}

void transaktionsliste::handleButton() {
    int tid = TStransaktionen->at(((QPushButton*)sender())->objectName().toInt());
    Erfassen erfassen;
    erfassen.setModal(true);
    erfassen.loadTransaktion(tid);
    erfassen.exec();
}
