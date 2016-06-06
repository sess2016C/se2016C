#include "hauptmenue_adm.h"
#include "ui_hauptmenue_adm.h"
#include "haushaltsverwaltung.h"
#include "benutzerverwaltung.h"
#include "kategorieverwaltung.h"
Haushaltsverwaltung *newHaupmenuWindowAdm = 0;
QTableWidget *tableAdm;

hauptmenue_adm::hauptmenue_adm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hauptmenue_adm)
{
    ui->setupUi(this);

    // Transaktionstabelle
    tableAdm = ui->tbl_Transaktionen;

    tableAdm->horizontalHeader()->setStretchLastSection(true);
    tableAdm->setRowCount(10);
    tableAdm->setColumnCount(6);
    tableAdm->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Datum")));
    tableAdm->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Betrag")));
    tableAdm->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Kategorie")));
    tableAdm->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Quelle")));
    tableAdm->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Zahlungsart")));
    tableAdm->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("")));

    for( int i = 0; i < tableAdm->rowCount(); i++ ){
        tableAdm->setCellWidget( i, 5, new QPushButton(QString("Details") ));
    }

}

hauptmenue_adm::~hauptmenue_adm()
{
    delete ui;
}

void hauptmenue_adm::on_btn_Benutzerverwaltung_clicked()
{
    Benutzerverwaltung benutzerverwaltung;
    benutzerverwaltung.setModal(true);
    benutzerverwaltung.exec();
}

void hauptmenue_adm::on_btn_Kategorieverwaltung_clicked()
{
    Kategorieverwaltung kategorieverwaltung;
    kategorieverwaltung.setModal(true);
    kategorieverwaltung.exec();
}

void hauptmenue_adm::on_btn_Abmelden_clicked()
{
    this->hide();
    newHaupmenuWindowAdm = new Haushaltsverwaltung();
    newHaupmenuWindowAdm->show();

}
