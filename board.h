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
    bool turnto_red;

    void paintEvent(QPaintEvent*);//棋盘
    void drawstone(QPainter&painter,int id);//棋子
    void mouseReleaseEvent(QMouseEvent*);//走棋

    QPoint center(int row,int col);//重构函数
    QPoint center(int id);//获取棋子坐标

    bool getRowCol(QPoint pt,int&row,int&col); //获取行列坐标

    bool canMove(int moveid,int row,int col,int killid );
    bool canMoveJiang(int moveid,int row,int col );
    bool canMoveShi(int moveid,int row,int col );
    bool canMoveChe(int moveid,int row,int col );
    bool canMoveMa(int moveid,int row,int col );
    bool canMovePao(int moveid,int row,int col ,int killid);
    bool canMoveXiang(int moveid,int row,int col );
    bool canMoveZu(int moveid,int row,int col );

    bool tryGo(int moveid,int row,int col ,int killid);
    int stoneAtLine(int row, int col, int prerow, int precol);
    int stoneOccupies(int row,int col);
signals:

};

#endif // BOARD_H
