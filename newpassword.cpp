#include "newpassword.h"
#include "ui_newpassword.h"
#include "QString"
#include "global.h"

/**
 * @brief NewPassword::NewPassword
 * @param parent
 * Öffnet den Dialog zur Änderung des Passworts.
 */
NewPassword::NewPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPassword)
{
    ui->setupUi(this);
}

/**
 * @brief NewPassword::~NewPassword
 * Destruktor der Klasse.
 */
NewPassword::~NewPassword()
{
    delete ui;
}

/**
 * @brief NewPassword::on_btn_NpAendern_clicked
 * Liest die Daten aus den Textfeldern und
 * aktualisiert den entsprechenden Datensatz
 * in der Datenbank.
 */
void NewPassword::on_btn_NpAendern_clicked()
{
    QString pw1 = ui->txt_NpPasswort1->text();
    QString pw2 = ui->txt_NpPasswort2->text();
    QString uName = benutzer_akt->getName();
    QString uVname = benutzer_akt->getVname();
    QString ugeb = benutzer_akt->getGeb();
    if(pw1 == pw2) {
        db->changebenutzerData(uName, uVname, pw1, ugeb);
        this->hide();
    } else {
        //TODO keine übereinstimmenden Passwörter
    }
}

/**
 * @brief NewPassword::on_btn_ErAbbrechen_clicked
 * Schließt den Dialog zum Ändern des Passworts.
 */
void NewPassword::on_btn_ErAbbrechen_clicked()
{
    this->hide();
}
