#include "board.h"
#include <QPainter>
Board::Board(QWidget *parent)
    : QWidget{parent}
{
    //调用函数初始化
    for(int i=0;i<32;i++){
        _s[i].initialize(i);
    }
}

void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    const int l=40;//偏移量，不能够直接在左上角
    _r=l/2;

    //画棋盘
    //下面绘制横纵，十条横线，九条竖线
    //横线
    for(int i=1;i<=10;i++){
        painter.drawLine(QPoint(l,i*l),QPoint(9*l,i*l));
    }
    // //竖线
    for(int i=1;i<=9;i++){
        if(i==1||i==9){
            painter.drawLine(QPoint(i*l,l),QPoint(i*l,10*l));

        }
        else{
            painter.drawLine(QPoint(i*l,l),QPoint(i*l,5*l));
            painter.drawLine(QPoint(i*l,6*l),QPoint(i*l,10*l));
        }
    }
    //斜线
    painter.drawLine(QPoint(4*l,l),QPoint(6*l,3*l));
    painter.drawLine(QPoint(6*l,l),QPoint(4*l,3*l));
    painter.drawLine(QPoint(4*l,8*l),QPoint(6*l,10*l));
    painter.drawLine(QPoint(6*l,8*l),QPoint(4*l,10*l));


    //画棋子
    for(int i=0;i<32;i++){
        drawstone(painter,i);
    }
}
//通过两个重构函数，获得棋子的像素坐标
//注意一下，要在类中声明重构
QPoint Board::center(int row,int col){
    QPoint ret;
    //这里使用rx(),可以修改值，x()不可以
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}
QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);
}

//画棋子
void Board::drawstone(QPainter&painter,int id){
    //棋子的中心坐标
    QPoint c= center(id);
    //棋子所在的矩形坐标
    QRect rect=QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    //画外面的圆
    painter.setBrush(QBrush(QColor(255,255,0)));
    painter.drawEllipse( center(id),_r,_r);
    //写棋名
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}
