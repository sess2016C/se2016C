#include "erfassen.h"
#include "ui_erfassen.h"
#include <QMessageBox>
#include <QString>
#include "global.h"
#include "dbmanager.h"
#include <QSqlQuery>
#include "QRegExp"
#include <QRegExpValidator>

Erfassen::Erfassen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Erfassen)
{

    ui->setupUi(this);
    updateComboBox();
    QRegExp rx ("[0-9]{12}");
    QRegExp rx2 ("[0-9]{2}");
    ui->txt_erf_amount->setValidator(new QRegExpValidator (rx, this));
    ui->txt_decimal->setValidator(new QRegExpValidator (rx2, this));
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
    QStringList lst = date.split(".");
    date = lst[2] + "-" + lst[1] + "-" + lst[0];
    QString amount_decimal = ui->txt_decimal->text();
    QString amount_txt = ui->txt_erf_amount->text();
    if(amount_txt == "") {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte geben Sie einen Betrag an!");
        msgBoxEr.exec();
        return;
    }
    if(amount_decimal == "") {
        amount_decimal = "00";
    } else if(amount_decimal.length() == 1){
        amount_decimal = amount_decimal + "0";
    }
    QString amounttxt = amount_txt + amount_decimal;
    qint64 amount = amounttxt.toLongLong();
    QString cat = ui->combo_cat->currentText();
    QString source = ui->txt_erf_source->text();
    QString payment = ui->combo_paymentOption->currentText();
    QString desc = ui->txt_erf_description->toPlainText();
    bool einnahme = ui->rdbtn_einnahme->isChecked();
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
    int zID = 0;
    query.prepare("SELECT zID FROM Zahlart WHERE bez = (:payment) AND bID = (:bID)");
    query.bindValue(":payment", payment);
    query.bindValue(":bID", bID);
    if(query.exec()) {
        if(query.next()) {
            zID = query.value(0).toInt();
        }
    }
    //check for einnahme or ausgabe
    if(!einnahme) { amount *= -1; }
    //got all nessecary data
    if(db->addTransaction(desc, amount, date, source, catID, bID, zID)) {
        qDebug() << "transaction added";
    }
    else {
        qDebug() << "something went wrong";
    }


    this->hide();
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
    ui->combo_paymentOption->addItem("");
    while(query.next()) {
        ui->combo_paymentOption->addItem(query.value(0).toString());
    }
}
