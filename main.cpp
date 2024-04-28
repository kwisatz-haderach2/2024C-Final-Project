#include "Start.h"
#include<QMediaPlayer>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QMediaPlayer *player = new QMediaPlayer;
    player->setSource(QUrl("qrc:/music/res/background_music.mp3"));
    player->setLoops(60);
    player->play();



    start w;
    w.show();
    return a.exec();
}
