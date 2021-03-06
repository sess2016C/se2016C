#include "bezahlart.h"
#include "ui_bezahlart.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "dbmanager.h"
#include "global.h"
#include "QMessageBox"

Bezahlart::Bezahlart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bezahlart)
{
    ui->setupUi(this);
    updateList();

}

Bezahlart::~Bezahlart()
{
    delete ui;
}

void Bezahlart::on_btn_BeAbbrechen_clicked()
{
    this->hide();
}

void Bezahlart::on_btn_BeHinzufuegen_clicked()
{
    QString bez = ui->txt_zahlart->text();
    if(bez == "") {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte geben Sie eine Zahlart an!");
        msgBoxEr.exec();
        return;
    }
    if(db->addPayment(bez, benutzer_akt->getUID())) {
        qDebug() << "payment added";
        updateList();
    }


}

void Bezahlart::on_btn_BeLoeschen_clicked()
{
    if(ui->list_bezahlart->currentItem() == NULL) {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte wählen Sie das zu löschende Element aus!");
        msgBoxEr.exec();
        return;
    }
    QString bez = ui->list_bezahlart->currentItem()->text();
    if(bez == "") return;
    if(db->delPayment(bez, benutzer_akt->getUID())) {
        updateList();
        qDebug() << "payment deleted";
    }


}

void Bezahlart::updateList() {
    ui->list_bezahlart->clear();
    QSqlQuery query;
    query.prepare("SELECT bez FROM Zahlart WHERE bid = (:bID)");
    query.bindValue(":bID", benutzer_akt->getUID());
    query.exec();
    while(query.next()) {
        ui->list_bezahlart->addItem(query.value(0).toString());
    }
}
