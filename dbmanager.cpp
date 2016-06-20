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

int DBManager::connectbenutzer(QString &email, QString &pwd) { //0 = fehlgeschlagen, 1 = okey, 2 = anmeldung mit standardpass
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
           benutzer_akt = new benutzer(bID, admin, email, geb, name, vname, pwd);
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

void DBManager::disconnectbenutzer() {
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

bool DBManager::addbenutzer(QString &email, QString &name, QString &vname, QString &geb) {
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
            qDebug() << "benutzer already existing: " << bid;
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

bool DBManager::delbenutzer(QString &email) {
    QSqlQuery query;
    query.prepare("DELETE FROM Benutzer WHERE email = (:email)");
    query.bindValue(":email", email);
    if(query.exec()) {
        return true;
    }
    qDebug() << "del benutzer didnt work";
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

bool DBManager::addTransaction(int tID, QString &beschr, qint64 betr, QString &date, QString &quelle, int kID, int bID, int zID) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Transaktion WHERE tid = (:tid)");
    query.bindValue(":tid", tID);
    query.exec();
    if(query.next()) {
        query.prepare("UPDATE Transaktion SET betrag = (:betrag), datum = (:datum), beschr = (:beschr), quelle = (:quelle), kID = (:kid), zID = (:zid) WHERE tid = (:tid)");
        query.bindValue(":betrag", betr);
        query.bindValue(":datum", date);
        query.bindValue(":beschr", beschr);
        query.bindValue(":quelle", quelle);
        query.bindValue(":kid", kID);
        query.bindValue(":zid", zID);
        query.bindValue(":tid", tID);
        if(query.exec()) {
            return true;
        }
        return false;
    } else {
        query.prepare("SELECT IFNULL(MAX(tID), 0) FROM Transaktion");
        query.exec();
        query.next();
        int count = query.value(0).toInt();

        query.prepare("INSERT INTO Transaktion(tID, betrag, datum, beschr, quelle, kID, bID, zID) VALUES (:tID, :betr, :date, :beschr, :quelle, :kID, :bID, :zID)");
        query.bindValue(":tID", count + 1);
        query.bindValue(":beschr", beschr);
        query.bindValue(":betr", betr);
        query.bindValue(":date", date);
        query.bindValue(":quelle", quelle);
        query.bindValue(":kID", kID);
        query.bindValue(":bID", bID);
        query.bindValue(":zID", zID);
        if(query.exec()) {
            return true;
        }
        qDebug() << query.lastError();
        return false;
    }

}

bool DBManager::changebenutzerData(QString &name, QString &vname, QString &pwd, QString &geb) {
    QSqlQuery query;
    query.prepare("UPDATE Benutzer SET geb = (:geb), name = (:name), vname = (:vname), pwd = (:pwd) WHERE bID = (:bID)");
    query.bindValue(":geb", geb);
    query.bindValue(":name", name);
    query.bindValue(":vname", vname);
    query.bindValue(":pwd", pwd);
    query.bindValue(":bID", benutzer_akt->getUID());
    if(query.exec()) {
        qDebug() << "updated benutzer";
        benutzer_akt->setGeb(geb);
        benutzer_akt->setName(name);
        benutzer_akt->setVname(vname);
        benutzer_akt->setPwd(pwd);
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
        //already exists for this benutzer
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

QString DBManager::getPaymentText(int zid) {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Zahlart WHERE zID = (:zid) AND bid = (:bid)");
    query.bindValue(":zid", zid);
    query.bindValue(":bid", benutzer_akt->getUID());
    query.exec();
    query.next();
    return query.value(0).toString();
}

QString DBManager::getCategoryText(int kid) {
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie WHERE kid = (:kid)");
    query.bindValue(":kid", kid);
    query.exec();
    query.next();
    return query.value(0).toString();
}

bool DBManager::cleanTables(){
    QSqlQuery delTrans;
    delTrans.prepare("DELETE FROM Transaktion");
    QSqlQuery delUser;
    delUser.prepare("DELETE FROM Benutzer");
    QSqlQuery delCategory;
    delCategory.prepare("DELETE FROM Kategorie");
    QSqlQuery delPayment;
    delPayment.prepare("DELETE FROM Zahlart");
    return delCategory.exec() && delPayment.exec() && delTrans.exec() && delUser.exec();
}

void DBManager::setupTestData(){
    QSqlQuery addAdmin;
    addAdmin.prepare("INSERT INTO Benutzer (bid, email, pwd, vname, name, administrator, geb) VALUES (1, 'rd@hs.aa', 'RD', 'Roland', 'Dietrich', 0, '2000-01-01')");
    if(addAdmin.exec()) {

    } else {
        qDebug() << addAdmin.lastError();
    }
    QString gehalt = "Gehaltseingang";
    db->addCategory(gehalt);
    QString lebensmittel = "Lebensmittel";
    db->addCategory(lebensmittel);
    QString freizeit = "Freizeit";
    db->addCategory(freizeit);

    QString email = "km@hs.aa";
    QString n = "Musterfrau";
    QString v = "Klara";
    QString date = "2000-01-01";
    db->addbenutzer(email, n, v, date);
    email = "mm@hs.aa";
    n = "Mustersohn";
    v = "Max";
    db->addbenutzer(email, n, v, date);

    QString p = "Bar";
    db->addPayment(p, 1);
    p = "Überweisung";
    db->addPayment(p, 2);
    p = "Kreditkarte";
    db->addPayment(p, 3);
                                                //kid, bid, zid
    QString empty = "";
    QString quelle = "C&A";
    db->addTransaction(1,empty, 200 ,date, quelle, 1, 1, 1);
    quelle = "Kik";
    db->addTransaction(2,empty, 300 ,date, quelle, 2, 1, 1);
    quelle = "Müller";
    db->addTransaction(3,empty, 150 ,date, quelle, 1, 2, 2);
    quelle = "Schlecker";
    db->addTransaction(4,empty, 550 ,date, quelle, 2, 2, 2);
    quelle = "Edeka";
    db->addTransaction(5,empty, 50  ,date, quelle, 3, 3, 3);
    quelle = "Penny";
    db->addTransaction(6,empty, 160 ,date, quelle, 3, 3, 3);
    quelle = "Lidl";
    db->addTransaction(7,empty, 1980,date, quelle, 3, 1, 1);
    quelle = "Aldi";
    db->addTransaction(8,empty, 1670,date, quelle, 3, 2, 2);
    quelle = "Rewe";
    db->addTransaction(9,empty, 120, date, quelle, 3, 3, 3);
    quelle = "Kaufland";
    db->addTransaction(10,empty, 10 ,date, quelle, 3, 1, 1);
}
