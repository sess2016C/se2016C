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
#include "transaktionsliste.h"
#include <QSqlQuery>

Haushaltsverwaltung *newHaupmenuWindowAdm = 0;
QTableWidget *tableAdm;
QTableWidget *negativ_benutzers;
QList <int> *transaktionen; //hier werden transaktionsids der angezeigten transaktionen gespeichert

hauptmenue_adm::hauptmenue_adm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hauptmenue_adm)
{
    ui->setupUi(this);
    if(!benutzer_akt->isAdmin()) {
        ui->btn_Benutzerverwaltung->setVisible(false);
        ui->btn_Kategorieverwaltung->setVisible(false);
        ui->label_benutzer_im_minus->setVisible(false);
        ui->tbl_negativebenutzers->setVisible(false);
    } else {
        //Fill list_benutzer_im_minus
        negativ_benutzers = ui->tbl_negativebenutzers;
        negativ_benutzers->horizontalHeader()->setStretchLastSection(true);
        negativ_benutzers->setColumnCount(2);
        negativ_benutzers->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Benutzer")));
        negativ_benutzers->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Saldo")));
        QSqlQuery query;
        query.prepare("SELECT bID, sum(betrag) FROM Transaktion WHERE bid != (:bid) GROUP BY bID");
        query.bindValue(":bid", benutzer_akt->getUID());
        int count = getTableRowCount(query);
        negativ_benutzers->setRowCount(count);
        count = 0;
        if(query.exec()) {
            int row = 0;
            while(query.next()) {
                int bid = query.value(0).toInt();
                qint64 saldo = query.value(1).toLongLong();
                if(saldo >= 0) { continue; }
                count++;
                QSqlQuery getEmail;
                getEmail.prepare("SELECT email FROM Benutzer WHERE bid = (:bid)");
                getEmail.bindValue(":bid", bid);
                getEmail.exec();
                getEmail.next();
                QString benutzer = getEmail.value(0).toString();
                negativ_benutzers->setItem(row, 0, new QTableWidgetItem(benutzer));
                negativ_benutzers->setItem(row, 1, new QTableWidgetItem(convertNumberToSaldo(saldo)));
                row++;
            }
        }
        negativ_benutzers->setRowCount(count);
    }
    // Transaktionstabelle
    tableAdm = ui->tbl_Transaktionen;

    tableAdm->horizontalHeader()->setStretchLastSection(true);
    tableAdm->setRowCount(10);
    tableAdm->setColumnCount(6);


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

    tableAdm->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Datum")));
    tableAdm->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Betrag")));
    tableAdm->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Kategorie")));
    tableAdm->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Quelle")));
    tableAdm->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Zahlungsart")));
    tableAdm->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("")));

    QSqlQuery query;
    query.prepare("SELECT * FROM Transaktion WHERE bID = (:bid) ORDER BY date(datum) DESC Limit (:lim)");
    query.bindValue(":bid", benutzer_akt->getUID());
    query.bindValue(":lim", QString::number(rows));
    if(query.exec()) {
        int table_row = 0;
        transaktionen = new QList<int>;
        while(query.next()) {
            transaktionen->append(query.value(0).toInt());
            QString datum = query.value(2).toString();
            datum = convertDate(datum);
            QString betrag = query.value(1).toString();
            qint64 betr = betrag.toLongLong();
            bool einnahme = true;
            if(betr < 0) { einnahme = false; }
            betrag = convertNumberToSaldo(betr);
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
            QPushButton *btn = new QPushButton("Details");
            btn->setObjectName(QString::number(table_row));
            tableAdm->setCellWidget(table_row, 5, btn ); //how to programm these buttons
            connect(btn, SIGNAL (released()), this, SLOT (handleButton()));
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

qint64 hauptmenue_adm::getSaldo(int benutzerID) {
    QSqlQuery query;
    query.prepare("SELECT sum(betrag) FROM Transaktion WHERE bID = (:bid)");
    query.bindValue(":bid", benutzerID);
    if(query.exec()) {
        if(query.next()) {
            qint64 saldo = query.value(0).toLongLong();
            return saldo;
        }
    }
    return -1;
}

//convert qin64 to saldo string
QString hauptmenue_adm::convertNumberToSaldo(qint64 number) {
    return QString::number(number / 100) + "," + QString::number(abs(number / 10 % 10)) + QString::number(abs(number % 10)) + " €";
}

void hauptmenue_adm::handleButton() {
    int tid = transaktionen->at(((QPushButton*)sender())->objectName().toInt());
    Erfassen erfassen;
    erfassen.setModal(true);
    erfassen.loadTransaktion(tid);
    erfassen.exec();
    updateTable(10);
}

void hauptmenue_adm::on_btn_transaktionsliste_clicked()
{
    transaktionsliste tliste;
    tliste.setModal(true);
    tliste.exec();
    updateTable(10);
}
