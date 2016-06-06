#include "kategorieverwaltung.h"
#include "ui_kategorieverwaltung.h"

Kategorieverwaltung::Kategorieverwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kategorieverwaltung)
{
    ui->setupUi(this);
}

Kategorieverwaltung::~Kategorieverwaltung()
{
    delete ui;
}

void Kategorieverwaltung::on_btn_KvAbbrechen_clicked()
{
    this->hide();
}
