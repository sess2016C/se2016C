#include "dbmanager.h"
#include "global.h"
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

DBManager::DBManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qDebug() << "Error Database connection";
    }
    else {
        qDebug() << "Databaseconnection OK";
    }
}


bool DBManager::isOpen() {
    return m_db.isOpen();
}

bool DBManager::isEmpty() {
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM Benutzer");
    query.exec();
    query.next();
    if(query.value(0).toInt() == 0) {
        return true;
    }
    return false;
}

int DBManager::connectUser(QString &email, QString &pwd) { //0 = fehlgeschlagen, 1 = okey, 2 = anmeldung mit standardpass
    QSqlQuery query;
    query.prepare("SELECT * FROM Benutzer WHERE email = (:email) AND pwd = (:pwd)");
    query.bindValue(":email", email);
    query.bindValue(":pwd", pwd);
    if(query.exec()) {
       while(query.next()) {
           QString curr_pw = query.value(6).toString();
           int bID = query.value(0).toInt();
           bool admin = query.value(1).toInt() == 0 ? true : false;
           QString email = query.value(2).toString();
           QString geb = query.value(3).toString();
           QString name = query.value(4).toString();
           QString vname = query.value(5).toString();
           QString pwd = query.value(6).toString();
           user = new User(bID, admin, email, geb, name, vname, pwd);
           if(curr_pw == "0000") {//Standardpasswort
                return 2;
           }
           else {
               return 1;
           }
       }
    }
    return 0;
}

void DBManager::disconnectUser() {
    if(m_db.isOpen()) {
        m_db.close();
    }
}

bool DBManager::addCategory(QString &category) {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie WHERE bez = (:cat)"); //Überprüfung, ob Kategorie schon vorhanden
    query.bindValue(":cat", category);
    query.exec();
    if(query.next()) {
        return false;
    }
    query.prepare("SELECT IFNULL(MAX(kID), 0) FROM Kategorie");
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    query.prepare("INSERT INTO Kategorie (kID, bez) VALUES ((:c), (:bez))");
    query.bindValue(":c", count + 1);
    query.bindValue(":bez", category);
    if(query.exec()) {
        return true;
    }
    qDebug() << query.lastError();
    return false;
}

bool DBManager::resetPW(QString &email) {
    QSqlQuery query;
    query.prepare("UPDATE Benutzer SET pwd = '0000' WHERE email = (:email)");
    query.bindValue(":email", email);
    if(query.exec()) {
        return true;
    }
    return false;
}

bool DBManager::addUser(QString &email, QString &name, QString &vname, QString &geb) {
    QSqlQuery query;
    if(email == "" or name == "" or vname == "" or geb == "") {
        qDebug() << "something was empty";
        return false; //insert data
    }
    query.prepare("SELECT * FROM Benutzer WHERE email = (:email)");
    query.bindValue(":email", email);
    if(query.exec()) {
        if(query.next()) {
            int bid = query.value(0).toInt();
            qDebug() << "user already existing: " << bid;
            return false; //already existing
        }
    }

    query.prepare("SELECT IFNULL(MAX(bID), 0) FROM Benutzer");
    query.exec();
    query.next();
    int count = query.value(0).toInt();
    query.prepare("INSERT INTO Benutzer (bID, administrator, email, geb, name, vname, pwd) VALUES ((:bID), (:admin), (:email), (:geb), (:name), (:vname), (:stdpw))");
    query.bindValue(":bID", count + 1);
    if(count == 0) {
        query.bindValue(":admin", 0); //true
    } else {
        query.bindValue(":admin", 1); //false
    }
    query.bindValue(":email", email);
    query.bindValue(":geb", geb);
    query.bindValue(":name", name);
    query.bindValue(":vname", vname);
    query.bindValue(":stdpw", "0000");
    //Standardpasswort = 0000
    if(query.exec()) {
        return true;
    }
    qDebug() << query.lastError();
    return false;
}

bool DBManager::delUser(QString &email) {
    QSqlQuery query;
    query.prepare("DELETE FROM Benutzer WHERE email = (:email)");
    query.bindValue(":email", email);
    if(query.exec()) {
        return true;
    }
    qDebug() << "del User didnt work";
    qDebug() << query.lastError();
    return false;
}

bool DBManager::delCat(QString &category){
    QSqlQuery query;
    query.prepare("DELETE FROM Kategorie WHERE bez = (:cat)");
    query.bindValue(":cat", category);
    if(query.exec()) {
        return true;
    }
    return false;
}

bool DBManager::addTransaction(QString &beschr, int betr, QString &date, QString &quelle, int kID, int bID, int zID) {
    QSqlQuery query;
    query.prepare("SELECT IFNULL(MAX(tID), 0) FROM Transaktion");
    query.exec();
    query.next();
    int count = query.value(0).toInt();

    query.prepare("INSERT INTO Transaktion(tID, betrag, datum, beschr, quelle, kID, bID, zID) VALUES ((:tID), (:beschr), (:betr), (:date), (:quelle), (:kID), (:bID), (:zID)");
    query.bindValue(":tID", count + 1);
    query.bindValue(":beschr", beschr);
    query.bindValue(":betr", betr);
    query.bindValue(":date", date);
    query.bindValue(":quelle)", quelle);
    query.bindValue(":kID", kID);
    query.bindValue(":bID", bID);
    query.bindValue(":zID", zID);
    if(query.exec()) {
        return true;
    }
    return false;
}

bool DBManager::changeUserData(QString &name, QString &vname, QString &pwd, QString &geb) {
    QSqlQuery query;
    query.prepare("UPDATE Benutzer SET geb = (:geb), name = (:name), vname = (:vname), pwd = (:pwd) WHERE bID = (:bID)");
    query.bindValue(":geb", geb);
    query.bindValue(":name", name);
    query.bindValue(":vname", vname);
    query.bindValue(":pwd", pwd);
    query.bindValue(":bID", user->getUID());
    if(query.exec()) {
        qDebug() << "updated user";
        user->setGeb(geb);
        user->setName(name);
        user->setVname(vname);
        user->setPwd(pwd);
        return true;
    }
    qDebug() << query.lastError();
    return false;
}

bool DBManager::addPayment(QString &pay, int uID) {
    QSqlQuery query;
    //Check if option already exists
    query.prepare("SELECT * FROM Zahlart WHERE bez = (:pay) AND bID = (:bID)");
    query.bindValue(":pay", pay);
    query.bindValue(":bID", uID);
    query.exec();
    if(query.next()) {
        return false;
        //already exists for this user
    }

    //get new zID
    query.prepare("SELECT IFNULL(MAX(zID), 0) FROM Zahlart");
    query.exec();
    query.next();
    int zID = query.value(0).toInt() + 1;

    //insert new paymentoption
    query.prepare("INSERT INTO Zahlart (zID, bez, bID) VALUES ((:zID), (:bez), (:bID))");
    query.bindValue(":zID", zID);
    query.bindValue(":bez", pay);
    query.bindValue(":bID", uID);
    if(query.exec()) {
        return true;
    }
    qDebug() << query.lastError();
    return false;
}

bool DBManager::delPayment(QString &pay, int uID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Zahlart WHERE bez = (:pay) AND bID = (:uID)");
    query.bindValue(":pay", pay);
    query.bindValue(":uID", uID);
    if(query.exec()) { return true; }
    return false;
}
