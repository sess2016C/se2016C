#include "hauptmenue.h"
#include "ui_hauptmenue.h"
#include "haushaltsverwaltung.h"
#include "erfassen.h"
#include "abrechnung.h"
#include "bezahlart.h"
#include "benutzerdaten.h"
# include <QtGui>
Haushaltsverwaltung *newHauptmenuWindow = 0;
QTableWidget *table;

Hauptmenue::Hauptmenue(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hauptmenue)
{
    ui->setupUi(this);

    table = ui->tbl_Transaktionen;

    table->horizontalHeader()->setStretchLastSection(true);
    table->setRowCount(10);
    table->setColumnCount(6);
    table->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Datum")));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Betrag")));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Kategorie")));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Quelle")));
    table->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Zahlungsart")));
    table->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("")));

    for( int i = 0; i < table->rowCount(); i++ ){
        table->setCellWidget( i, 5, new QPushButton(QString("Details") ));
    }

}

Hauptmenue::~Hauptmenue()
{
    delete ui;
}


void Hauptmenue::on_btn_Abmelden_clicked()
{
    this->hide();
    newHauptmenuWindow = new Haushaltsverwaltung();
    newHauptmenuWindow->show();
}


void Hauptmenue::on_btn_Erfassen_clicked()
{
    Erfassen erfassen;
    erfassen.setModal(true);
    erfassen.exec();
}

void Hauptmenue::on_btn_Abrechnung_clicked()
{
    Abrechnung abrechnung;
    abrechnung.setModal(true);
    abrechnung.exec();
}

void Hauptmenue::on_btn_Bezahlart_clicked()
{
    Bezahlart bezahlart;
    bezahlart.setModal(true);
    bezahlart.exec();
}

void Hauptmenue::on_btn_Benutzerdaten_clicked()
{
    Benutzerdaten benutzerdaten;
    benutzerdaten.setModal(true);
    benutzerdaten.exec();
}

void Hauptmenue::on_tbl_Transaktionen_activated(const QModelIndex &index)
{
    // Test ************************************************************
    int s;
    int row ,column;
    int zeilen =table->rowCount();
    int spalten= table->columnCount();
    int pos1,pos2,lastpos;
    QString line;
    QString eintrag[99][99];

    QString verzeichnis=QCoreApplication::applicationDirPath();
    verzeichnis.append("/data.txt");

    QFile datei(verzeichnis);
    if (datei.open(QIODevice::ReadOnly | QIODevice::Text)){
        QApplication::setOverrideCursor(Qt::WaitCursor);

        QTextStream in(&datei);
        while(!in.atEnd()){
            line = in.readLine();
            s=0;
            pos1=0;
            lastpos=0;
            while(pos1!=-1){
                pos1=line.indexOf("\"",lastpos);
                lastpos=pos1+1;
                pos2=line.indexOf("\"",lastpos);
                lastpos=pos2+1;
                if(pos1!=-1){
                    eintrag[zeilen][s]=line.mid((pos1+1),(pos2-pos1-1));
                    s++;
                }
            }
        }
    }
    //datei.close();

    for(row=0;row<zeilen;row++){
        for(column=0;column<spalten;column++){
            QTableWidgetItem *newItem = new QTableWidgetItem;
            newItem->setText(eintrag[row][column]);

            table->setItem(row, column, newItem);
        }
    }
    // Test ************************************************************

}
