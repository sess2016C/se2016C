#include "kategorieverwaltung.h"
#include "ui_kategorieverwaltung.h"
#include "dbmanager.h"
#include "global.h"
#include "QSqlQuery"

Kategorieverwaltung::Kategorieverwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kategorieverwaltung)
{
    ui->setupUi(this);
    updateList();

}

Kategorieverwaltung::~Kategorieverwaltung()
{
    delete ui;
}

void Kategorieverwaltung::on_btn_KvAbbrechen_clicked()
{
    this->hide();
}

void Kategorieverwaltung::on_btn_BeHinzufuegen_clicked()
{
    QString cat = ui->txt_newCategory->text();
    if(db->addCategory(cat)) {
        qDebug() << "cateogry added";
        updateList();
    }
}

void Kategorieverwaltung::updateList() {
    ui->list_category->clear();
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    while(query.next()) {
        ui->list_category->addItem(query.value(0).toString());
    }
}

void Kategorieverwaltung::on_btn_BeLoeschen_clicked()
{
    QString cat = ui->list_category->currentItem()->text();
    if(db->delCat(cat)) {
        qDebug() << cat << "deleted";
        updateList();
    }
}
