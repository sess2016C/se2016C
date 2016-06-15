#include "benutzerverwaltung.h"
#include "ui_benutzerverwaltung.h"
#include "global.h"
#include "dbmanager.h"
#include "QDebug"
#include "QString"
#include "QMessageBox"

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

void Benutzerverwaltung::on_btn_UserAnlegen_clicked()
{
    QString email = ui->txt_userEmail->text();
    QString vname = ui->txt_userVname->text();
    QString name = ui->txt_userName->text();
    QString geb = ui->txt_userGeb->text();
    if(email == "" or vname == "" or name == "" or geb == "") { //TODO talk about required values
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte füllen Sie alle Felder aus!");
        msgBoxEr.exec();
    } else {
        if(db->addUser(email, name, vname, geb)) {
            qDebug() << "user added";
        }

    }
}

void Benutzerverwaltung::on_btn_UserDel_clicked()
{
    QString email = ui->txt_delUserEmail->text();
    if(email == "") {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte geben Sie eine Emailadresse an!");
        msgBoxEr.exec();
        return;
    }
    if(email == user->getEmail()) {
        qDebug() << "cant delete current user because of admin";
        return;
    } else if(db->delUser(email)) {
        qDebug() << "user deleted";
    }
}

void Benutzerverwaltung::on_btn_UserResetPW_clicked() {
    QString email = ui->txt_UserResetPW->text();
    if(email == "") {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte geben Sie eine Emailadresse an!");
        msgBoxEr.exec();
        return;
    }
    if(db->resetPW(email)) {
        qDebug() << "user pw restet";
    }
}
