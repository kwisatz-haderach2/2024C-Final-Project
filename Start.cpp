#include "Start.h"
#include "ui_Start.h"
#include<QSoundEffect>
#include<QToolButton>
#include<QSoundEffect>

QSoundEffect *music = new QSoundEffect;
start::start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);


    this->resize(600,550);

    this->setWindowIcon(QIcon(":/image/res/OIP-removebg-preview.png"));
    this->setWindowIconText("中国象棋");
//背景
    QPixmap *pixmap = new QPixmap(":/image/res/R-removebg-preview.png");
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);


    //播放音频
    music->setSource(QUrl::fromLocalFile(":/music/res/background_music.wav"));
    music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    music->setVolume(0.3f);  //设置音量，在0到1之间
    music->play();


}

start::~start()
{
    delete ui;
}

void start::on_pushButton_ManMan_clicked()
{
    this->close();
    music ->stop();
    b=new Board();
    b->show();

}


void start::on_pushButton_ManMachine_clicked()
{
    this->close();
    music ->stop();
    c=new singleGame();
    c->show();

}


