#include "stone.h"

stone::stone() {}
stone::~stone(){}
void stone::initialize(int id){
    _id=id;

    struct{
        int row;
        int col;
        stone::type type;

    }pos[16]={
                 {0,0,stone::Che},
                 {0,1,stone::Ma},
                 {0,2,stone::Xiang},
                 {0,3,stone::Shi},
                 {0,4,stone::Jiang},
                 {0,5,stone::Shi},
                 {0,6,stone::Xiang},
                 {0,7,stone::Ma},
                 {0,8,stone::Che},

                 {2,1,stone::Pao},
                 {2,7,stone::Pao},

                 {3,0,stone::Bing},
                 {3,2,stone::Bing},
                 {3,4,stone::Bing},
                 {3,6,stone::Bing},
                 {3,8,stone::Bing},
                 };
    if(_id<16){
        _row=pos[id].row;
        _col=pos[id].col;
        _type=pos[id].type;
    }
    else{
        _row=9-pos[id-16].row;
        _col=8-pos[id-16].col;
        _type=pos[id-16].type;
    };


    //0没死，id小于十六为红方
    _dead=false;
    _camp =(_id<16);
};

QString stone::getText(){
    {
        switch(this->_type){
        case Jiang:
            return"将";
        case Shi:
            return"士";
        case Xiang:
            return "相";
        case Ma:
            return"马";
        case Che:
            return"车";
        case Pao:
            return"炮";
        case Bing:
            return"兵";
        default:
            return "错误！";
        }

    }
}
