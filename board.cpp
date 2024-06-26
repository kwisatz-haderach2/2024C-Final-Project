#include "board.h"
#include <QPainter>
#include<QMouseEvent>


Board::Board(QWidget *parent)
    : QWidget{parent}
{

    //调用函数初始化
    for(int i=0;i<32;i++){
        _s[i].initialize(i);
    }

    turnto_red=true;
    _selected=-1;
}


//画棋盘
void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    const int l=40;//偏移量，不能够直接在左上角
    _r=l/2;

    //下面绘制横纵，十条横线，九条竖线
    //横线
    for(int i=1;i<=10;i++){
        painter.drawLine(QPoint(l,i*l),QPoint(9*l,i*l));
    }
    // //竖线
    for(int i=1;i<=9;i++){
        if(i==1||i==9){
            painter.drawLine(QPoint(i*l,l),QPoint(i*l,10*l));

        }
        else{
            painter.drawLine(QPoint(i*l,l),QPoint(i*l,5*l));
            painter.drawLine(QPoint(i*l,6*l),QPoint(i*l,10*l));
        }
    }
    //斜线
    painter.drawLine(QPoint(4*l,l),QPoint(6*l,3*l));
    painter.drawLine(QPoint(6*l,l),QPoint(4*l,3*l));
    painter.drawLine(QPoint(4*l,8*l),QPoint(6*l,10*l));
    painter.drawLine(QPoint(6*l,8*l),QPoint(4*l,10*l));


    //画棋子并且摆在棋盘上
    for(int i=0;i<32;i++){
        drawstone(painter,i);
    }
}


//每次画面刷新的时候，画未死棋子位置形状
void Board::drawstone(QPainter&painter,int id){

    //1.看是否还在棋盘上
    if(_s[id]._dead)
        return;

    //2.获取两种位置（形状，中心坐标和所在矩形）
    //棋子的中心坐标
    QPoint c= center(id);
    //棋子所在的矩形坐标
    QRect rect=QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);//左侧，上侧，长，宽

    //3.上色+轮廓+汉字
    //上色，被选中灰色，一般黄色
    if(id==_selected){//如果是第一次点击的棋子
        painter.setBrush(QBrush(Qt::gray));
    }
    else{
        painter.setBrush(QBrush(Qt::yellow));
    }

    //画外面的圆
    painter.setPen(Qt::black);//每次画都要更新一下笔
    painter.drawEllipse( center(id),_r,_r);

    //写棋名
    if(_s[id]._camp){
        painter.setPen(Qt::red);
    }
    painter.setFont(QFont("隶书",_r,1000));
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}


//重构函数获得像素坐标，但这里不一定有棋子
//第一个函数一定是交叉点不一定是棋子，第二个一定是棋子
QPoint Board::center(int row,int col){
    QPoint ret;
    //这里使用rx(),可以修改值，x()不可以
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}
QPoint Board::center(int id){
    return center(_s[id]._row,_s[id]._col);
}


//看鼠标在哪个交叉点的半径范围内
//而不是看在哪个棋子范围内
bool Board::getRowCol(QPoint pt ,int& row,int&col){
    for(row=0;row<=9;row++){
        for(col=0;col<=8;col++){
            QPoint cc=center(row,col);
            int dx=cc.x()-pt.x();//交叉点中心-鼠标中心
            int dy=cc.y()-pt.y();

            //若在棋子半径范围内，选中
            if(dx*dx+dy*dy<_r*_r){
                return true;
            }
        }
    }
    return false;
}


//走法
//将
bool Board::canMoveJiang(int moveid,int row,int col){
    //红黑
    if(_s[moveid]._camp){
        if(row<7)
            return false;
    }
    else{
        if(row>2)
            return false;
    }
    if(col<3||col>5)
        return false;

    //一次走一格
    int dx = abs(_s[moveid]._row - row);
    int dy = abs(_s[moveid]._col - col);
    if ((dx == 1 && dy== 0) || (dx == 0 && dy == 1))
        return true;

    return false;
}
//士
bool Board::canMoveShi(int moveid,int row,int col ){

    //红黑
    if(_s[moveid]._camp){
        if(row<7)
            return false;
    }
    else{
        if(row>2)
            return false;
    }
    if(col<3||col>5)
        return false;

    //一次走斜线
    int dx= abs(_s[moveid]._row - row);
    int dy = abs(_s[moveid]._col - col);
    if (dx == 1 && dy== 1)
        return true;

    return false;
}
//车
bool Board::canMoveChe(int moveid,int row,int col ){

    //车只能走直线，而且不能跳子
    int dx= abs(_s[moveid]._row - row);
    int dy = abs(_s[moveid]._col - col);
    if ((!dx || !dy) && !stoneAtLine(row, col, _s[moveid]._row, _s[moveid]._col))
        return true;
    return false;
}
//马
bool Board::canMoveMa(int moveid,int row,int col ){

    int dx= abs(_s[moveid]._row - row);
    int dy = abs(_s[moveid]._col - col);
    //行列走法
    if(dx==1&&dy==2){
        if(stoneOccupies(_s[moveid]._row,(_s[moveid]._col+col)/2)==-1)
            return true;
    }
    if(dx==2&&dy==1){
        if(stoneOccupies((_s[moveid]._row+row)/2,_s[moveid]._col)==-1)
            return true;
    }

    return false;
}
//炮
bool Board::canMovePao(int moveid,int row,int col,int killid){

    //吃棋
    if(killid!=-1 && stoneAtLine(_s[moveid]._row,_s[moveid]._col,row,col)==1){
        return true;
    }
    //不吃棋
    if(killid==-1 && stoneAtLine(_s[moveid]._row,_s[moveid]._col,row,col)==0)
        return true;
    return false;
}
//相
bool Board::canMoveXiang(int moveid,int row,int col ){

    int dx= abs(_s[moveid]._row - row);
    int dy = abs(_s[moveid]._col - col);
    if (dx != 2 || dy != 2)
        return false;

    //蹩相腿
    int mx=(_s[moveid]._row+row)/2;
    int my=(_s[moveid]._col+col)/2;
    if(stoneOccupies(mx,my)!=-1)
        return false;
    //不能过河
    if (_s[moveid]._camp)
    {
        if (row < 4)
            return false;
    }
    else
    {
        if (row > 5)
            return false;
    }

    return true;

}
//卒
bool Board::canMoveZu(int moveid,int row,int col ){
    //未过楚河汉界之前，只能前进；过后，可前后左右移动；每次只能移动一格
    int dx = _s[moveid]._row - row;
    int absdx = abs(_s[moveid]._row - row);
    int absdy = abs(_s[moveid]._col - col);
    //红方
    if(_s[moveid]._camp){
        if(row>4){
            if (dx == 1 && absdy == 0)
                return true;
        }
        else if(row<5){
            if ((absdx == 1 && absdy == 0) || (absdy == 1 && absdx == 0))
                return true;
        }
    }
    //黑子
    else{
        if(row < 5){
            if (dx == -1 && absdy == 0)
                return true;
        }
        else if(row>4){
            if ((absdx == 1 && absdy == 0) || (absdy == 1 && absdx == 0))
                return true;
        }
    }

    return false;
}

//某个位置是否有棋子，有的话返回id
int Board::stoneOccupies(int row, int col)
{
    //遍历棋子
    for (int i = 0; i < 32; i++)
    {
        if (_s[i]._row == row && _s[i]._col == col && !_s[i]._dead)
            return i;
    }
    return -1;
}

//同行/列两点之间之间棋子的个数 将帅，炮
int Board::stoneAtLine(int row1, int col1, int row2, int col2)
{
    int num = 0;
    //不在同一行/列
    if (row1 != row2 && col1 != col2)
        return -1;
    //两点重合，未移动
    if (row1 == row2 && col1 == col2)
        return -1;
    //同一行，两点之间按列遍历，每点判断是否有棋子
    if (row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for (int i = min + 1; i < max; i++)
        {
            if (stoneOccupies(row1, i) != -1)
                num++;
        }
    }
    //同一列，两点之间按行遍历，每点判断是否有棋子
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for (int i = min + 1; i < max; i++)
        {
            if (stoneOccupies(i, col1) != -1)
                num++;
        }
    }
    return num;
}

//试走棋
bool Board::tryGo(int moveid,int row,int col ,int killid)
{
    //暂时存储
    int temprow = _s[moveid]._row;
    int tempcol = _s[moveid]._col;
    _s[moveid]._row = row;
    _s[moveid]._col = col;


    if (killid > 0)
        _s[killid]._dead = true;

    //如果走棋后将帅会面


    bool b = true;
    //若在同一列，中间无子，且都活着
    if (_s[4]._col == _s[20]._col && stoneAtLine(_s[4]._row, _s[4]._col, _s[20]._row, _s[20]._col) == 0 && !_s[4]._dead && !_s[20]._dead)
    {
        _s[moveid]._row = temprow;
        _s[moveid]._col = tempcol;
        b = false;
    }
    _s[moveid]._row = temprow;
    _s[moveid]._col = tempcol;
    if (killid > 0)
        _s[killid]._dead = false;
    return b;
}


bool Board::canMove(int moveid,int row,int col,int killid ){
    //共同要求，将帅不碰面，不同色
    if(killid!=-1&&_s[moveid]._camp==_s[killid]._camp){
        //换选择
        _selected=killid;
        update();
        return false;

    }
    if (!tryGo(moveid,row,col,killid))
    {
        return false;
    }
    //每种棋子
    switch (_s[ moveid]._type)
    {
    case stone::RSHUAI:
    case stone::BJIANG:
        return canMoveJiang(moveid, row, col);
        break;
    case stone::RSHI:
    case stone::BSHI:
        return canMoveShi(moveid, row, col);
        break;
    case stone::RJU:
    case stone::BJU:
        return canMoveChe( moveid, row, col);
        break;
    case stone::BMA:
    case stone::RMA:
        return canMoveMa( moveid, row, col);
        break;
    case stone::BPAO:
    case stone::RPAO:
        return canMovePao( moveid, row, col,killid);
        break;
    case stone::RXIANG:
    case stone::BXIANG:
        return canMoveXiang( moveid, row, col);
        break;
    case stone::BZU:
    case stone::RBING:
        return canMoveZu( moveid, row, col);
        break;
    }
    return true;
};
//走棋要点击两次
//第一次是否点击到
//第二次是否点击到棋子，未点击棋子，点击交叉点还是棋盘外
//不对，第一次点击中了棋子，那就是不能放下选择其他的，否则是悔棋！！！
//每次点击屏幕，都会调用该函数
void Board::mouseReleaseEvent(QMouseEvent *m){
    //获取鼠标位置，pt代表象棋的行列值
    QPoint pt=m->pos();

    //判断有无棋子
    int row,col;//交叉点坐标，调用getRowCol会改值，成为棋子坐标
    bool Ret=getRowCol(pt,row,col);

    //点击到外边，这里需要加入
    //不在任何一个棋子的范围内


    //这里第一二次点击都会判断
    //点击的是不是交叉点
    if(Ret==false){
        return;
    }

    int i;
    int _clicked=-1;

    //通过循环判断选中的是哪个棋子
    for(i=0;i<32;i++){
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead==false){
            break;
        }
    }
    //如果循环找到了，那么i一定小于32，否则i==32
    //要是没找到，i==32，但是clicked还等于-1，这样后面判断第二次是否点击到棋子的时候会判断
    if(i<32){
        _clicked=i;
    }

    //下面进行点击判断

    //若第一次点击
    if(_selected==-1){
        //clickded若不等于-1，则点击到某一棋子，而不是棋盘外
        if(_clicked!=-1){
            if(turnto_red ==_s[_clicked]._camp){
                _selected=_clicked;//确定第一次点击的谁，选中了这个棋子
                update();//然后在update后更新该棋子的颜色
            }

        }

        //若第一次点击到棋盘外或者未点击棋子
        //实际上在此mouseReleaseEvent调用时Ret就未false不会进来
        //也就不需要else
    }
    //若第二次点击未点击棋子，分点击交叉点和棋盘外
    //          到棋子，吃
    else{
        if(canMove(_selected,row,col,_clicked)){
            //先移动第一次点击的棋子
            _s[_selected]._row=row;
            _s[_selected]._col=col;

            //杀掉第二次选的棋子
            if(_clicked!=-1){//click!=-1就说明选中了棋子，且不是同一方
                _s[_clicked]._dead=true;
            }
            turnto_red=!turnto_red;
            _selected=-1;
            update();
        }

    }
}
