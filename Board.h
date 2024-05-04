#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    stone _s[32];
    int _offSet=50;//偏移量
    int _r=_offSet/2-2;//棋子半径
    int _selected;//选中的棋子
    bool turnto_red;//轮到谁


    void paintEvent(QPaintEvent*);//棋盘
    void drawstone(QPainter&painter,int id);//棋子
    void mouseReleaseEvent(QMouseEvent*);//走棋
    void rightSingle(QPainter &painter,QPoint id,int r_or_f);//绘制棋盘中的直角
    virtual void click(int row,int col,int _clicked);
    void victory();

    QPoint center(int row,int col);
    QPoint center(int id);//获取棋子坐标

    bool getRowCol(QPoint pt,int&row,int&col); //看点击处是否有棋子

    //走棋规则
    bool canMove(int moveid,int row,int col,int killid );
    bool canMoveJiang(int moveid,int row,int col );
    bool canMoveShi(int moveid,int row,int col );
    bool canMoveChe(int moveid,int row,int col );
    bool canMoveMa(int moveid,int row,int col );
    bool canMovePao(int moveid,int row,int col ,int killid);
    bool canMoveXiang(int moveid,int row,int col );
    bool canMoveZu(int moveid,int row,int col );



    bool tryGo(int moveid,int row,int col ,int killid);//试走
    int stoneAtLine(int row, int col, int prerow, int precol);//同行/列两点之间之间棋子的个数
    int stoneOccupies(int row,int col);//某处是否有棋子，有的话返回id

private:
signals:

};

#endif // BOARD_H
