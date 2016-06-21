#include "kategorieverwaltung.h"
#include "ui_kategorieverwaltung.h"
#include "dbmanager.h"
#include "global.h"
#include "QSqlQuery"

/**
 * @brief Kategorieverwaltung::Kategorieverwaltung
 * @param parent
 * Öffnet den Dialog zur Verwaltung der Kategorien.
 * Anschließend wird die Kategorienliste aktualisiert.
 */
Kategorieverwaltung::Kategorieverwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kategorieverwaltung)
{
    ui->setupUi(this);
    updateList();

}

/**
 * @brief Kategorieverwaltung::~Kategorieverwaltung
 * Destruktor der Klasse.
 */
Kategorieverwaltung::~Kategorieverwaltung()
{
    delete ui;
}

/**
 * @brief Kategorieverwaltung::on_btn_KvAbbrechen_clicked
 * Schließt die Kategorieverwaltung.
 */
void Kategorieverwaltung::on_btn_KvAbbrechen_clicked()
{
    this->hide();
}

/**
 * @brief Kategorieverwaltung::on_btn_BeHinzufuegen_clicked
 * Fügt die eingetragene Kategorie der Liste hinzu.
 */
void Kategorieverwaltung::on_btn_BeHinzufuegen_clicked()
{
    QString cat = ui->txt_newCategory->text();
    if(db->addCategory(cat)) {
        qDebug() << "cateogry added";
        updateList();
    }
}

/**
 * @brief Kategorieverwaltung::updateList
 * Aktualisiert die Liste der Kategorien.
 */
void Kategorieverwaltung::updateList() {
    ui->list_category->clear();
    QSqlQuery query;
    query.prepare("SELECT bez FROM Kategorie");
    query.exec();
    while(query.next()) {
        ui->list_category->addItem(query.value(0).toString());
    }
}

/**
 * @brief Kategorieverwaltung::on_btn_BeLoeschen_clicked
 * Löscht eine ausgewählte Kategorie aus der Liste.
 */
void Kategorieverwaltung::on_btn_BeLoeschen_clicked()
{
    QString cat = ui->list_category->currentItem()->text();
    if(db->delCat(cat)) {
        qDebug() << cat << "deleted";
        updateList();
    }
}
