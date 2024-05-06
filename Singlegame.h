#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include"Board.h"
#include"step.h"
#include"QTimer"

class singleGame : public Board
{
    Q_OBJECT
public:
    int aheadStep = 3;

    singleGame (QWidget *parent = nullptr);
    ~singleGame ();

    virtual void click(int , int ,int );
    void getAllarea(QVector<Step *> &steps);               //获取可移动范围
    void saveSteps(int, int, int, int, QVector<Step *> &); //存棋

    void fakemove(Step *);//试走
    void backfakemove(Step *);//恢复状态

    Step *getBestScore();//最优方法
    int getMinScore(int, int);//每个节点的最值
    int getMaxScore(int, int);
    int finalScore();//这种方法的最后得分

signals:
public slots:
    void pcMove();//实现
};
#endif
