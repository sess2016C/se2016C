#include "benutzerdaten.h"
#include "ui_benutzerdaten.h"
#include "global.h"
#include "dbmanager.h"
#include <QMessageBox>

Benutzerdaten::Benutzerdaten(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Benutzerdaten)
{
    ui->setupUi(this);
    ui->txt_benutzerDataGeb->setDate(QDate::fromString(benutzer_akt->getGeb(), "dd.MM.yyyy"));
    ui->txt_benutzerDataName->setText(benutzer_akt->getName());
    ui->txt_benutzerDataVname->setText(benutzer_akt->getVname());
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
    QString geb = ui->txt_benutzerDataGeb->text();
    QString name = ui->txt_benutzerDataName->text();
    QString vname = ui->txt_benutzerDataVname->text();
    QString pwd = benutzer_akt->getPwd();
    if(geb != "" and name != "" and vname != "") {
        db->changebenutzerData(name, vname, pwd, geb);
        qDebug() << "changed some data";
        this->hide();
    } else {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte füllen Sie alle Felder aus!");
        msgBoxEr.exec();
    }

}
