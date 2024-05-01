#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "stone.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    stone _s[32];
    int _r;//棋子半径
    int _selected;


    void paintEvent(QPaintEvent*);//棋盘
    void drawstone(QPainter&painter,int id);//棋子
    void mouseReleaseEvent(QMouseEvent*);//走棋

    QPoint center(int row,int col);//重构函数
    QPoint center(int id);//获取棋子坐标

    bool getRowCol(QPoint pt,int&row,int&col); //获取行列坐标

    bool canMove(int moveid,int row,int col,int killid );
    bool canMove1(int moveid,int row,int col,int killid );
    bool canMove2(int moveid,int row,int col,int killid );
    bool canMove3(int moveid,int row,int col,int killid );
    bool canMove4(int moveid,int row,int col,int killid );
    bool canMove5(int moveid,int row,int col,int killid );
    bool canMove6(int moveid,int row,int col,int killid );
    bool canMove7(int moveid,int row,int col,int killid );


signals:
};

#endif // BOARD_H
