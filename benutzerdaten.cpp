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
    ui->txt_userDataGeb->setDate(QDate::fromString(user->getGeb(), "dd.MM.yyyy"));
    ui->txt_userDataName->setText(user->getName());
    ui->txt_userDataVname->setText(user->getVname());
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
    QString geb = ui->txt_userDataGeb->text();
    QString name = ui->txt_userDataName->text();
    QString vname = ui->txt_userDataVname->text();
    QString pwd = user->getPwd();
    if(geb != "" and name != "" and vname != "") {
        db->changeUserData(name, vname, pwd, geb);
        qDebug() << "changed some data";
    }
    this->hide();
}
