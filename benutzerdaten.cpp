#include "benutzerdaten.h"
#include "ui_benutzerdaten.h"
#include <QMessageBox>

Benutzerdaten::Benutzerdaten(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Benutzerdaten)
{
    ui->setupUi(this);
}

Benutzerdaten::~Benutzerdaten()
{
    delete ui;
}

void Benutzerdaten::on_btn_NuAbbrechen_clicked()
{
    this->hide();
}

void Benutzerdaten::on_btn_NuSpeichern_clicked()
{
    QMessageBox msgBoxEr;
    msgBoxEr.setText("Benutzerdaten gespeichert.");

    this->hide();
    msgBoxEr.exec();
}
