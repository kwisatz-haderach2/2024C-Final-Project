#ifndef STONE_H
#define STONE_H
#include<QString>
class stone
{
public:
    stone();
    ~stone();

    //棋子的基本属性
    enum type{BJIANG, BSHI,BZU, BPAO, BMA, BXIANG, BJU,
            RSHUAI, RSHI,RBING, RPAO, RMA,RXIANG, RJU};
    int _row;
    int _col;
    int _id;//独一无二
    bool _dead;
    type _type;
    bool _camp;

    //初始化函数,对每个棋子都调用
    void initialize(int id);

    QString getText();
};

#endif // STONE_H
