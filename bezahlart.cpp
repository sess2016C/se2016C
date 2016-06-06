#include "bezahlart.h"
#include "ui_bezahlart.h"
#include <QMessageBox>
QListWidget *list;

Bezahlart::Bezahlart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bezahlart)
{
    ui->setupUi(this);

    list = ui->listWidget;

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
    QString val = ui->txt_neueBez->text();
    if(val != NULL){
        list->addItem(val);

        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bezahlart erfolgreich erfasst.");

        msgBoxEr.exec();
    }

}

void Bezahlart::on_btn_BeLoeschen_clicked()
{
    qDeleteAll(list->selectedItems());

}
