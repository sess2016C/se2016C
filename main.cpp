#include "haushaltsverwaltung.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Haushaltsverwaltung w;
    w.show();

    return a.exec();
}
