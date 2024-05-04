#include "Stone.h"
stone::stone() {}
stone::~stone(){}
void stone::initialize(int id){

    _id=id;

    struct{
        int row;
        int col;
        type type;
    }pos[32]={
        {0, 0, BJU},
        {0, 1, BMA},
        {0, 2, BXIANG},
        {0, 3, BSHI},
        {0, 4, BJIANG},
        {0, 5, BSHI},
        {0, 6, BXIANG},
        {0, 7, BMA},
        {0, 8, BJU},
        {2, 1, BPAO},//10
        {2, 7, BPAO},//11
        {3, 0, BZU},
        {3, 2, BZU},
        {3, 4, BZU},
        {3, 6, BZU},
        {3, 8, BZU},

        {9, 0, RJU},
        {9, 1, RMA},
        {9, 2, RXIANG},
        {9, 3, RSHI},
        {9, 4, RSHUAI},
        {9, 5, RSHI},
        {9, 6, RXIANG},
        {9, 7, RMA},
        {9, 8, RJU},
        {7, 1, RPAO},//26
        {7, 7, RPAO},//27
        {6, 0, RBING},
        {6, 2, RBING},
        {6, 4, RBING},
        {6, 6, RBING},
        {6, 8, RBING}
    };

    //画每个棋子
    _row=pos[id].row;
    _col=pos[id].col;
    _type=pos[id].type;

    //0没死，id大于15红方
    _dead=false;
    _camp =(_id>15);//1为红
};

QString stone::getText(){
    {
        switch(this->_type){
        case BJIANG:
            return QStringLiteral("將");
        case BSHI:
            return QStringLiteral("士");
        case BZU:
            return QStringLiteral("卒");
        case BPAO:
            return QStringLiteral("炮");
        case BMA:
            return QStringLiteral("馬");
        case BXIANG:
            return QStringLiteral("象");
        case BJU:
            return QStringLiteral("車");


        case RSHUAI:
            return QStringLiteral("帥");
        case RSHI:
            return QStringLiteral("士");
        case RBING:
            return QStringLiteral("兵");
        case RPAO:
            return QStringLiteral("炮");
        case RMA:
            return QStringLiteral("馬");
        case RXIANG:
            return QStringLiteral("相");
        case RJU:
            return QStringLiteral("車");
        default:
            return "错误";
        }

    }
}
