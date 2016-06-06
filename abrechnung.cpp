#include "abrechnung.h"
#include "ui_abrechnung.h"
QTableWidget *abTable;

Abrechnung::Abrechnung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Abrechnung)
{
    ui->setupUi(this);

    abTable = ui->tbl_AbTable;

    abTable->horizontalHeader()->setStretchLastSection(true);
    abTable->setRowCount(10);
    abTable->setColumnCount(2);
    abTable->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Kategorie")));
    abTable->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Saldo")));

}

Abrechnung::~Abrechnung()
{
    delete ui;
}

void Abrechnung::on_btn_AbAbbrechen_clicked()
{
    this->hide();
}
