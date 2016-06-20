#include "erfassen.h"
#include "ui_erfassen.h"
#include "hauptmenue_adm.h"
#include <QMessageBox>
#include <QString>
#include "global.h"
#include "dbmanager.h"
#include <QSqlQuery>
#include "QRegExp"
#include <QRegExpValidator>

/**
 * @brief tID
 * Transaktions-ID
 */
int tID = 0;

/**
 * @brief Erfassen::Erfassen
 * @param parent
 * Öffnet den Dialog zum Erfassen von Transaktionen, befüllt
 * die einzelnen Comboboxen (Kategorie/Zahlart) mit den entsprechenden
 * Werten und belegt die Betrag-Felder mit einem Validator, um Falscheingaben
 * vorzubeugen.
 */
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

/**
 * @brief Erfassen::~Erfassen
 * Destruktor der Klasse.
 */
Erfassen::~Erfassen()
{
    delete ui;
}

/**
 * @brief Erfassen::on_btn_ErAbbrechen_clicked
 * Schließt diesen Dialog bei Betätigung.
 */
void Erfassen::on_btn_ErAbbrechen_clicked()
{
    this->hide();
}

/**
 * @brief Erfassen::on_btn_ErErfassen_clicked
 * Liest die einzelnen Benutzereingaben aus den
 * entsprechenden Formularfeldern und fügt diese
 * in die Datenbank ein. (Transaktion erfassen)
 * Danach wird der Dialog geschlossen.
 */
void Erfassen::on_btn_ErErfassen_clicked()
{
    QString d = ui->txt_erf_date->text();
    QString date = hauptmenue_adm::convertDate(d); //TODO test
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
    if(cat == "") {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Erfassen Sie zuerst eine Kategorie!");
        msgBoxEr.exec();
        return;
    }
    QString source = ui->txt_erf_source->text();
    QString payment = ui->combo_paymentOption->currentText();
    QString desc = ui->txt_erf_description->toPlainText();
    bool einnahme = ui->rdbtn_einnahme->isChecked();
    int bID = benutzer_akt->getUID();

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
    if(db->addTransaction(tID, desc, amount, date, source, catID, bID, zID)) {
        qDebug() << "transaction saved";
    }
    else {
        qDebug() << "something went wrong";
    }


    this->hide();
}

/**
 * @brief Erfassen::updateComboBox
 * Liest die eingetragenen Kategorien und
 * Zahlarten aus der Datenbank und initialisiert
 * die entsprechenden Comboboxen.
 */
void Erfassen::updateComboBox() {
    ui->combo_cat->clear();
    ui->combo_paymentOption->clear();
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    while(query.next()) {
        ui->combo_cat->addItem(query.value(0).toString());
    }
    query.prepare("SELECT bez FROM Zahlart WHERE bid = (:bid)");
    query.bindValue(":bid", benutzer_akt->getUID());
    query.exec();
    ui->combo_paymentOption->addItem("");
    while(query.next()) {
        ui->combo_paymentOption->addItem(query.value(0).toString());
    }
}

/**
 * @brief Erfassen::loadTransaktion
 * @param tid
 * Initialisiert die Formularfelder mit den
 * bereits vorhandenen Daten aus der Daten-
 * bank anhand der übergebenen Transaktions-ID.
 * (Transaktion bearbeiten (Detailansicht))
 */
void Erfassen::loadTransaktion(int tid) {
    tID = tid;
    QSqlQuery query;
    query.prepare("SELECT * FROM Transaktion WHERE tid = (:tid)");
    query.bindValue(":tid", tid);
    query.exec();
    query.next();
    QString d = query.value(2).toString();
    QString da = hauptmenue_adm::convertDate(d);
    QDate date = QDate::fromString(da, "DD.MM.YYYY");
    ui->txt_erf_date->setDate(date);
    qint64 amount = query.value(1).toLongLong() / 100;
    int dec1 = query.value(1).toLongLong() / 10 % 10;
    int dec2 = query.value(1).toLongLong() % 10;
    if(amount < 0) {
        ui->txt_erf_amount->setText(QString::number(amount * -1));
    }
    else {
        ui->txt_erf_amount->setText(QString::number(amount));
    }
    ui->txt_decimal->setText(QString::number(dec1) + QString::number(dec2));
    if(amount < 0) {
        ui->rdbtn_ausgabe->setChecked(true);
        ui->rdbtn_einnahme->setChecked(false);
    }
    updateComboBox();
    QString category = db->getCategoryText(query.value(5).toInt());
    int index = ui->combo_cat->findText(category);
    ui->combo_cat->setCurrentIndex(index);
    ui->txt_erf_source->setText(query.value(4).toString());
    ui->txt_erf_description->setText(query.value(3).toString());
    QString payment = db->getPaymentText(query.value(7).toInt());
    index = ui->combo_paymentOption->findText(payment);
    ui->combo_paymentOption->setCurrentIndex(index);
}
