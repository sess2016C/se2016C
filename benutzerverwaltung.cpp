#include "benutzerverwaltung.h"
#include "ui_benutzerverwaltung.h"

Benutzerverwaltung::Benutzerverwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Benutzerverwaltung)
{
    ui->setupUi(this);
}

Benutzerverwaltung::~Benutzerverwaltung()
{
    delete ui;
}

void Benutzerverwaltung::on_btn_BvAbbrechen_clicked()
{
    this->hide();
}
