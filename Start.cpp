#include "Start.h"
#include "ui_Start.h"

start::start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);

    QPixmap *pixmap = new QPixmap(":/image/res/R__2_-removebg-preview.png");
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);

}

start::~start()
{
    delete ui;
}



void start::on_pushButton_ManMachine_clicked()
{
    this->close();
    b=new Board();
    b->show();
}

