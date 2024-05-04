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

    void fakemove(Step *);
    void backfakemove(Step *);

    Step *getBestScore();
    int getMinScore(int, int);
    int getMaxScore(int, int);
    int finalScore();

signals:
public slots:
    void pcMove();
};
#endif
