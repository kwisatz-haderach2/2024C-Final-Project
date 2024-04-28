#ifndef STONE_H
#define STONE_H
#include<QString>
class stone
{
public:
    stone();
    ~stone();

    //棋子的基本属性
    enum type{Jiang,Shi,Xiang,Ma,Che,Pao,Bing};
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
