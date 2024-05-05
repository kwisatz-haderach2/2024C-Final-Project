#include "Start.h"
#include <QApplication>
#include<QSoundEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    start w;
    w.show();
    return a.exec();
}
