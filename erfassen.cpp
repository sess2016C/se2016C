#include "erfassen.h"
#include "ui_erfassen.h"
#include <QMessageBox>
#include <QString>
#include "global.h"
#include "dbmanager.h"
#include <QSqlQuery>

Erfassen::Erfassen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Erfassen)
{

    ui->setupUi(this);
    updateComboBox();
}

Erfassen::~Erfassen()
{
    delete ui;
}

void Erfassen::on_btn_ErAbbrechen_clicked()
{
    this->hide();
}

void Erfassen::on_btn_ErErfassen_clicked()
{
    QString date = ui->txt_erf_date->text();
    QString amounttmp = ui->txt_erf_amount->text();
    int amount = amounttmp.toInt();
    QString cat = ui->combo_cat->currentText();
    QString source = ui->txt_erf_source->text();
    QString payment = ui->combo_paymentOption->currentText();
    QString desc = ui->txt_erf_description->toPlainText();
    int bID = user->getUID();

    //get Category ID
    int catID;
    QSqlQuery query;
    query.prepare("SELECT kID FROM Kategorie WHERE bez = (:bez)");
    query.bindValue(":bez", cat);
    if(query.exec()) {
        if(query.next()) {
            catID = query.value(0).toInt();
        }
    }
    //get payment ID
    int zID;
    query.prepare("SELECT zID FROM Zahlart WHERE bez = (:payment) AND bID = (:bID)");
    query.bindValue(":payment", payment);
    query.bindValue(":bID", bID);
    if(query.exec()) {
        if(query.next()) {
            zID = query.value(0).toInt();
        }
    }
    //got all nessecary data
    if(db->addTransaction(desc, amount, date, source, catID, bID, zID)) {
        qDebug() << "transaction added";
    } else {
        qDebug() << "something went wrong";
    }


    this->hide();
    //QMessageBox msgBoxEr;
    //msgBoxEr.setText("Transaktion erfolgreich erfasst.");
    //msgBoxEr.exec();
}

void Erfassen::updateComboBox() {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    while(query.next()) {
        ui->combo_cat->addItem(query.value(0).toString());
    }
    query.prepare("SELECT bez FROM Zahlart WHERE bid = (:bid)");
    query.bindValue(":bid", user->getUID());
    query.exec();
    while(query.next()) {
        ui->combo_paymentOption->addItem(query.value(0).toString());
    }
}
