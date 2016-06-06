#include "user.h"

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

bool User::isAdmin(){
    return admin;
}

int User::getUID() {
    return uID;
}
