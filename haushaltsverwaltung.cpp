#include "haushaltsverwaltung.h"
#include "ui_haushaltsverwaltung.h"
#include <QMessageBox>
#include "hauptmenue.h"
#include "hauptmenue_adm.h"
#include "erstanmeldung_adm.h"
#include "dbmanager.h"
#include "global.h"

Hauptmenue *newWindow = 0;
static const QString path = "haus.db";
DBManager *db = NULL;
hauptmenue_adm *newWindowadm = 0;

Haushaltsverwaltung::Haushaltsverwaltung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Haushaltsverwaltung)
{
    if(db == NULL) {
        db = new DBManager(path);
    }
    //erstanmeldung
    //abfrage ob benutzertabelle leer
    if(db->isEmpty()) {
        //erstanmeldung
        erstanmeldung();
    }
    else {
        ui->setupUi(this);
    }
}

Haushaltsverwaltung::~Haushaltsverwaltung()
{
    delete ui;
}

void Haushaltsverwaltung::erstanmeldung(){
    Erstanmeldung_adm erstanmeldung_adm;
    erstanmeldung_adm.setModal(true);
    erstanmeldung_adm.exec();
}

void Haushaltsverwaltung::on_btn_ABeenden_clicked()
{
    exit(0);
}

void Haushaltsverwaltung::on_btn_AAnmelden_clicked()
{
    QString benutzername = ui->txt_Benutzername->text();
    QString passwort = ui->txt_Passwort->text();

    if(db->isOpen()) {
        //qDebug() << "connected";
    } else {
        //qDebug() << "NOT connected";
        exit(0); //TODO MSGBox mit retry
    }
    int ret = db->connectUser(benutzername, passwort);
    if(ret == 1) {
        this->hide();
        if(user->isAdmin()) {
            newWindowadm = new hauptmenue_adm();
            newWindowadm->show();
        } else {
            newWindow = new Hauptmenue();
            newWindow->show();
        }


    } else if(ret == 0){
        QMessageBox msgBoxAn;
        msgBoxAn.setText("Falscher Benutzername oder Passwort.");
        msgBoxAn.exec();
    } else if(ret == 2) {
        //Anmeldung mit Standardpasswort
        qDebug() << "anmeldung mit stdpw";
        this->hide();
        newWindow = new Hauptmenue();
    }

}

void Haushaltsverwaltung::on_txt_Passwort_returnPressed()
{
    on_btn_AAnmelden_clicked();
}
