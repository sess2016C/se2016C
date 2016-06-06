#include "erfassen.h"
#include "ui_erfassen.h"
#include <QMessageBox>

Erfassen::Erfassen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Erfassen)
{
    ui->setupUi(this);
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
    QMessageBox msgBoxEr;
    msgBoxEr.setText("Transaktion erfolgreich erfasst.");

    this->hide();
    msgBoxEr.exec();
}
