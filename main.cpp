#include "haushaltsverwaltung.h"
#include "global.h"
#include <QApplication>

/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 * Hauptklasse des Projekts.
 * Ruft das Login-Fenster auf.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Haushaltsverwaltung w;
    w.show();

    return a.exec();
}
