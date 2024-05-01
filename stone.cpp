#include "stone.h"
#include"board.h"
stone::stone() {}
stone::~stone(){}
void stone::initialize(int id){
    _id=id;

    struct{
        int row;
        int col;
        stone::type type;
    }pos[32]={
        {0, 0, stone::BJU},
        {0, 1, stone::BMA},
        {0, 2, stone::BXIANG},
        {0, 3, stone::BSHI},
        {0, 4, stone::BJIANG},
        {0, 5, stone::BSHI},
        {0, 6, stone::BXIANG},
        {0, 7, stone::BMA},
        {0, 8, stone::BJU},
        {2, 1, stone::BPAO},
        {2, 7, stone::BPAO},
        {3, 0, stone::BZU},
        {3, 2, stone::BZU},
        {3, 4, stone::BZU},
        {3, 6, stone::BZU},
        {3, 8, stone::BZU},

        {9, 0, stone::RJU},
        {9, 1, stone::RMA},
        {9, 2, stone::RXIANG},
        {9, 3, stone::RSHI},
        {9, 4, stone::RSHUAI},
        {9, 5, stone::RSHI},
        {9, 6, stone::RXIANG},
        {9, 7, stone::RMA},
        {9, 8, stone::RJU},
        {7, 1, stone::RPAO},
        {7, 7, stone::RPAO},
        {6, 0, stone::RBING},
        {6, 2, stone::RBING},
        {6, 4, stone::RBING},
        {6, 6, stone::RBING},
        {6, 8, stone::RBING}
    };

    //画每个棋子

    //调用initialize的时候就是用的_s.[i]，所以不用_s[_di]._row
    _row=pos[id].row;
    _col=pos[id].col;
    _type=pos[id].type;

    //0没死，id小于十六为true，红方
    _dead=false;
    _camp =(_id<16);//1为红
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
