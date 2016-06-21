#include "benutzerdaten.h"
#include "ui_benutzerdaten.h"
#include "global.h"
#include "dbmanager.h"
#include <QMessageBox>

/**
 * @brief Benutzerdaten Konstruktor für die Benutzeroberfläche des Dialogs "Benutzerdaten ändern",
 * in dem der Benutzer seine persönlichen Daten abrufen und ändern kann.
 * @param parent Standardparameter
 */
Benutzerdaten::Benutzerdaten(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Benutzerdaten)
{
    ui->setupUi(this);
    ui->txt_benutzerDataGeb->setDate(QDate::fromString(benutzer_akt->getGeb(), "dd.MM.yyyy"));
    ui->txt_benutzerDataName->setText(benutzer_akt->getName());
    ui->txt_benutzerDataVname->setText(benutzer_akt->getVname());
}

/**
 * @brief ~Benutzerdaten Destruktor der Klasse "Benutzerdaten".
 */
Benutzerdaten::~Benutzerdaten()
{
    delete ui;
}

/**
 * @brief on_btn_NuAbbrechen_clicked Slot des Buttons "Abbrechen".
 */
void Benutzerdaten::on_btn_NuAbbrechen_clicked()
{
    this->hide();
}

/**
 * @brief on_btn_NuSpeichern_clicked Slot des Buttons "Speichern". Hier werden die Daten übernommen, welche der
 * Benutzer eingetragen hat.
 */
void Benutzerdaten::on_btn_NuSpeichern_clicked()
{
    QString geb = ui->txt_benutzerDataGeb->text();
    QString name = ui->txt_benutzerDataName->text();
    QString vname = ui->txt_benutzerDataVname->text();
    QString pwd = benutzer_akt->getPwd();
    if(geb != "" and name != "" and vname != "") {
        db->changebenutzerData(name, vname, pwd, geb);
        qDebug() << "changed some data";
        this->hide();
    } else {
        QMessageBox msgBoxEr;
        msgBoxEr.setText("Bitte füllen Sie alle Felder aus!");
        msgBoxEr.exec();
    }

}
