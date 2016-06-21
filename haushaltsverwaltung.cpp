#include "haushaltsverwaltung.h"
#include "ui_haushaltsverwaltung.h"
#include <QMessageBox>
#include "hauptmenue_adm.h"
#include "erstanmeldung_adm.h"
#include "dbmanager.h"
#include "global.h"
#include "newpassword.h"

static const QString path = "../haus.db";
DBManager *db = NULL;
hauptmenue_adm *newWindowadm = 0;

/**
 * @brief Haushaltsverwaltung::Haushaltsverwaltung
 * @param parent
 * Öffnet den Dialog zur Anmeldung am System (wenn
 * kein Benutzer in der Datenbank vorhanden ist, wird
 * die Erstanmeldung ausgeführt), baut eine Verbindung
 * zur Datenbank auf und reagiert mit dem "Zurücksetzen
 * der Datenbank auf Auslieferungszustand" bei der Übergabe
 * der Kommandozeilenparameters "clean" bzw. werden Test-
 * daten beim Parameter "test" in die Datenbank eingefügt.
 */
Haushaltsverwaltung::Haushaltsverwaltung(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Haushaltsverwaltung)
{
    if(db == NULL) {
        db = new DBManager(path);
    }
    //abfrage ob benutzertabelle leer
    if(QApplication::instance()->arguments().size() > 1) {
        QString argv = QApplication::instance()->arguments().at(1);
        if(argv == "clean") {
            db->cleanTables();
        } else if(argv == "test") {
            db->setupTestData();
        }
    }
    if(db->isEmpty()) {
        //erstanmeldung
        erstanmeldung();

    }
    ui->setupUi(this);
}

/**
 * @brief Haushaltsverwaltung::~Haushaltsverwaltung
 * Destruktor der Klasse.
 */
Haushaltsverwaltung::~Haushaltsverwaltung()
{
    delete ui;
}

/**
 * @brief Haushaltsverwaltung::erstanmeldung
 * Öffnet den Dialog zur Erstanmeldung für den
 * Administrator.
 */
void Haushaltsverwaltung::erstanmeldung(){
    Erstanmeldung_adm erstanmeldung_adm;
    erstanmeldung_adm.setModal(true);
    erstanmeldung_adm.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint);
    erstanmeldung_adm.exec();
}

/**
 * @brief Haushaltsverwaltung::newPassword
 * Öffnet den Dialog zur Passwortänderung.
 */
void Haushaltsverwaltung::newPassword(){
    NewPassword newPWDialog;
    newPWDialog.setModal(true);
    newPWDialog.exec();
}

/**
 * @brief Haushaltsverwaltung::on_btn_ABeenden_clicked
 * Beendet die Anwendung.
 */
void Haushaltsverwaltung::on_btn_ABeenden_clicked()
{
    exit(0);
}

/**
 * @brief Haushaltsverwaltung::on_btn_AAnmelden_clicked
 * Meldet den Benutzer mit den angegebenen Daten am System
 * an. Abgleich der eingegebenen Daten mit der Datenbank.
 */
void Haushaltsverwaltung::on_btn_AAnmelden_clicked()
{
    QString benutzername = ui->txt_Benutzername->text();
    QString passwort = ui->txt_Passwort->text();

    if(db->isOpen()) {
        //qDebug() << "connected";
    } else {
        //qDebug() << "NOT connected";
        return; //TODO MSGBox mit retry
    }
    int ret = db->connectbenutzer(benutzername, passwort);
    if(ret == 1) {
        this->hide();

        qDebug() << benutzer_akt->isAdmin();
        newWindowadm = new hauptmenue_adm();
        newWindowadm->show();


    } else if(ret == 0){
        QMessageBox msgBoxAn;
        msgBoxAn.setText("Falscher Benutzername oder Passwort.");
        msgBoxAn.exec();
    } else if(ret == 2) {
        //Anmeldung mit Standardpasswort
        //TODO do this shit
        qDebug() << "anmeldung mit stdpw";
        newPassword();
        newWindowadm = new hauptmenue_adm();
        newWindowadm->show();
        this->hide();
    }

}

/**
 * @brief Haushaltsverwaltung::on_txt_Passwort_returnPressed
 * Nach der Passwortänderung wird der aktuelle Benutzer
 * sogleich am System angemeldet.
 */
void Haushaltsverwaltung::on_txt_Passwort_returnPressed()
{
    on_btn_AAnmelden_clicked();
}
