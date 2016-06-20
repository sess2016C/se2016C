#include "benutzer.h"
#include "qdebug.h"

benutzer *benutzer_akt;

benutzer::benutzer(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd) {
    this->uID = uID;
    this->admin = admin;
    this->email = email;
    this->geb = geb;
    this->name = name;
    this->vname = vname;
    this->pwd = pwd;
}

bool benutzer::isAdmin(){ return admin; }

int benutzer::getUID() { return uID; }

QString benutzer::getEmail() { return email; }

QString benutzer::getGeb() { return geb; }

QString benutzer::getName() { return name; }

QString benutzer::getVname() { return vname; }

QString benutzer::getPwd() { return pwd; }

void benutzer::setGeb(QString &geb) { this->geb = geb; }

void benutzer::setName(QString &name) { this->name = name; }

void benutzer::setVname(QString &Vname) { this->vname = Vname; }

void benutzer::setPwd(QString &pwd) { this->pwd = pwd; }

bool benutzer::anmeldung(QString email, QString passwort) {

}
