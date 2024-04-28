#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "stone.h"
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);

    stone _s[32];

    //棋子半径，为什么不写在stone.h
    int _r;

    void drawstone(QPainter&painter,int id);

    //重构函数，获取棋子坐标
    QPoint center(int row,int col);
    QPoint center(int id);
signals:
};

#endif // BOARD_H
