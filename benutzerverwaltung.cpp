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

void Benutzerverwaltung::on_btn_benutzerAnlegen_clicked()
{
    QString email = ui->txt_benutzerEmail->text();
    QString vname = ui->txt_benutzerVname->text();
    QString name = ui->txt_benutzerName->text();
    QString geb = ui->txt_benutzerGeb->text();
    if(email == "" or vname == "" or name == "" or geb == "") { //TODO talk about required values
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte füllen Sie alle Felder aus!");
        msgBoxEr.exec();
    } else {
        if(db->addbenutzer(email, name, vname, geb)) {
            qDebug() << "benutzer added";
            QMessageBox msgBoxEr;
            msgBoxEr.setText("Nutzer erfolgreich angelegt!");
            msgBoxEr.exec();
        }

    }
    updateTable();
}

void Benutzerverwaltung::on_btn_benutzerDel_clicked()
{
    QString email = ui->lst_delbenutzer->currentItem()->text();
    if(db->delbenutzer(email)) {
        qDebug() << "benutzer deleted";
        updateTable();
    }
}

void Benutzerverwaltung::on_btn_benutzerResetPW_clicked() {
    QString email = ui->lst_resetbenutzerPW->currentItem()->text();
    if(db->resetPW(email)) {
        qDebug() << "benutzer pw restet";
        updateTable();
    }
}

void Benutzerverwaltung::updateTable() {
    ui->lst_delbenutzer->clear();
    ui->lst_resetbenutzerPW->clear();
    QSqlQuery query;
    query.prepare("SELECT email FROM Benutzer WHERE bID != (:bid)");
    query.bindValue(":bid", benutzer_akt->getUID());
    if(query.exec()) {
        while(query.next()) {
            ui->lst_delbenutzer->addItem(query.value(0).toString());
            ui->lst_resetbenutzerPW->addItem(query.value(0).toString());
        }
    }
}
