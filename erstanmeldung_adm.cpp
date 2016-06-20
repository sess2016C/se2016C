#include "erstanmeldung_adm.h"
#include "ui_erstanmeldung_adm.h"
#include "dbmanager.h"
#include "global.h"
#include "haushaltsverwaltung.h"

Haushaltsverwaltung *newLoginWindow = 0;

/**
 * @brief Erstanmeldung_adm::Erstanmeldung_adm
 * @param parent
 * Erstellt den Dialog zur Erstanmeldung eines
 * Admins.
 */
Erstanmeldung_adm::Erstanmeldung_adm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Erstanmeldung_adm)
{
    ui->setupUi(this);
}

/**
 * @brief Erstanmeldung_adm::~Erstanmeldung_adm
 * Destruktor der Klasse.
 */
Erstanmeldung_adm::~Erstanmeldung_adm()
{
    delete ui;
}

/**
 * @brief Erstanmeldung_adm::on_btn_EaBeenden_clicked
 * Button mit dem die Anwendung beendet wird.
 */
void Erstanmeldung_adm::on_btn_EaBeenden_clicked()
{
    exit(0);
}

/**
 * @brief Erstanmeldung_adm::on_btn_EaAnlegen_clicked
 * Erzeugt mit den angegebenen Daten einen neuen Admin-
 * User für das System. Danach wird der Dialog geschlossen.
 */
void Erstanmeldung_adm::on_btn_EaAnlegen_clicked()
{
    //TODO Prüfen auf Korrektheit der Eingaben
    QString email = ui->txt_EaEmail->text();
    QString name = ui->txt_EaNachname->text();
    QString vname = ui->txt_EaVorname->text();
    QString geb = ui->txt_EaGeburtsdatum->text();
    if(db->addbenutzer(email, name, vname, geb)) {
        this->hide();
    } else {
        //TODO Fehlerfall
    }
}
