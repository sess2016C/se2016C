#include "erstanmeldung_adm.h"
#include "ui_erstanmeldung_adm.h"
#include "dbmanager.h"
#include "global.h"
#include "haushaltsverwaltung.h"

Haushaltsverwaltung *newLoginWindow = 0;

Erstanmeldung_adm::Erstanmeldung_adm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Erstanmeldung_adm)
{
    ui->setupUi(this);
}

Erstanmeldung_adm::~Erstanmeldung_adm()
{
    delete ui;
}

void Erstanmeldung_adm::on_btn_EaBeenden_clicked()
{
    exit(0);
}

void Erstanmeldung_adm::on_btn_EaAnlegen_clicked()
{
    //TODO Prüfen auf Korrektheit der Eingaben
    QString email = ui->txt_EaEmail->text();
    QString name = ui->txt_EaNachname->text();
    QString vname = ui->txt_EaVorname->text();
    QString geb = ui->txt_EaGeburtsdatum->text();
    if(db->addUser(email, name, vname, geb)) {
        this->hide();
    } else {
        //TODO Fehlerfall
    }
}
