#include "haushaltsverwaltung.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Haushaltsverwaltung w;
    w.show();
    /*
    if(argc == 2){
        if(*argv[1] == 'c'){
            db->cleanTables();
            qDebug() << "Tables cleaned";
        }
        if(*argv[1] == 't'){
            db->setupTestData();
            qDebug() << "TestData deployed";
        }
    }
    else{
        qDebug() << "invalid parameters";
    }

    */

    return a.exec();
}
