#include "benutzerverwaltung.h"
#include "ui_benutzerverwaltung.h"
#include "global.h"
#include "dbmanager.h"
#include "QDebug"
#include "QString"
#include "QMessageBox"
#include <QSqlQuery>

Benutzerverwaltung::Benutzerverwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Benutzerverwaltung)
{
    ui->setupUi(this);
    updateTable();
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
            QMessageBox msgBoxEr;
            msgBoxEr.setText("Nutzer erfolgreich angelegt!");
            msgBoxEr.exec();
        }

    }
    updateTable();
}

void Benutzerverwaltung::on_btn_UserDel_clicked()
{
    QString email = ui->lst_delUser->currentItem()->text();
    if(db->delUser(email)) {
        qDebug() << "user deleted";
        updateTable();
    }
}

void Benutzerverwaltung::on_btn_UserResetPW_clicked() {
    QString email = ui->lst_resetUserPW->currentItem()->text();
    if(db->resetPW(email)) {
        qDebug() << "user pw restet";
        updateTable();
    }
}

void Benutzerverwaltung::updateTable() {
    ui->lst_delUser->clear();
    ui->lst_resetUserPW->clear();
    QSqlQuery query;
    query.prepare("SELECT email FROM Benutzer WHERE bID != (:bid)");
    query.bindValue(":bid", user->getUID());
    if(query.exec()) {
        while(query.next()) {
            ui->lst_delUser->addItem(query.value(0).toString());
            ui->lst_resetUserPW->addItem(query.value(0).toString());
        }
    }
}
