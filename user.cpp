#include "user.h"
#include "qdebug.h"

User *user;

User::User(int uID, bool admin, QString email, QString geb, QString name, QString vname, QString pwd) {
    this->uID = uID;
    this->admin = admin;
    this->email = email;
    this->geb = geb;
    this->name = name;
    this->vname = vname;
    this->pwd = pwd;
}

bool User::isAdmin(){ return admin; }

int User::getUID() { return uID; }

QString User::getEmail() { return email; }

QString User::getGeb() { return geb; }

QString User::getName() { return name; }

QString User::getVname() { return vname; }

QString User::getPwd() { return pwd; }

void User::setGeb(QString &geb) { this->geb = geb; }

void User::setName(QString &name) { this->name = name; }

void User::setVname(QString &Vname) { this->vname = Vname; }

void User::setPwd(QString &pwd) { this->pwd = pwd; }
