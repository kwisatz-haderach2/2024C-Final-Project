#include "Singlegame.h"
#include<QSoundEffect>

singleGame::singleGame(QWidget *parent) : Board(parent) {}
singleGame::~singleGame() {}

void singleGame::click(int row, int col,int _clicked)
{
    if (!turnto_red)
        return;
    //红棋由人走棋，调用board类的click函数
    Board::click(row, col,_clicked);
    //红棋走完轮到黑棋，由机器给出走法
    if (!turnto_red)
    {
        //设定一个计时器，红棋走完过1s黑棋再走
        QTimer::singleShot(1000, this, SLOT(pcMove()));
    }
}
//实现
void singleGame::pcMove()
{
    //得到最佳走法
    Step *step = getBestScore();

    //移动到的地方如果有棋子则吃棋
    if (step->secondclicked != -1)
    {
        _s[step->secondclicked]._dead = true;
    }

    //走棋

    _s[step->firstclicked]._row = step->rowto;
    _s[step->firstclicked]._col = step->colto;
    QSoundEffect *musicc = new QSoundEffect();

    musicc->setSource(QUrl::fromLocalFile(":/music/res/piece_move.wav"));
    musicc->setLoopCount(1);  //设置无限循环
    musicc->setVolume(0.5f);  //设置音量，在0到1之间
    musicc->play();


    delete step;

    victory();
    turnto_red = !turnto_red;
    update();
}

//可移动范围，嵌套的第一步
void singleGame::getAllarea(QVector<Step *> &steps)
{

    //黑棋红棋遍历棋子不同
    int min = 0, max = 16;

    if (turnto_red)//红棋
    {
        min = 16;
        max = 32;
    }
//把自己还活着的棋子试着走所有地方
    for (int i = min; i < max; i++)
    {
        if (_s[i]._dead)
            continue;
        for (int row = 0; row <= 9; row++)
        {
            for (int col = 0; col <= 8; col++)
            {
                int clicked = stoneOccupies(row, col); //有棋子
                if (clicked != -1 && !_s[clicked]._camp)
                    continue;
                if (canMove(i, row, col, clicked)) //判断能否走棋
                {
                    saveSteps(i, clicked, row, col, steps); //存棋
                }
                else
                    continue;
            }
        }
    }
}

//试走棋
void singleGame::fakemove(Step *step)
{
    _s[step->firstclicked]._row = step->rowto;
    _s[step->firstclicked]._col = step->colto;
    if (step->secondclicked > 0)
        _s[step->secondclicked]._dead = true;
    turnto_red = !turnto_red;
}

//退回
void singleGame::backfakemove(Step *step)
{
    _s[step->firstclicked]._row = step->rowfrom;
    _s[step->firstclicked]._col = step->colfrom;
    if (step->secondclicked > 0)
        _s[step->secondclicked]._dead = false;
    turnto_red=!turnto_red;
}

//保存走棋方法
void singleGame::saveSteps(int preclicked, int clicked, int row, int col, QVector<Step *> &steps)
{
    Step *step = new Step;
    step->colfrom = _s[preclicked]._col;
    step->colto = col;
    step->rowfrom = _s[preclicked]._row;
    step->rowto = row;
    step->firstclicked = preclicked;
    step->secondclicked = clicked;
    steps.append(step);
}

//得到最佳走法
Step *singleGame::getBestScore()
{
    QVector<Step *> steps;
    getAllarea(steps);

    int maxScore = -10000;

    Step *ret = nullptr;
    //遍历所有可能走法
    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        int score = getMinScore(aheadStep - 1, maxScore);
        backfakemove(step);

        if (score > maxScore)
        {
            maxScore = score;
            if (ret)
                delete ret;
            ret = step;
        }
        else
        {
            delete step;
        }
    }
    return ret;
}

//对方棋子得分最小
int singleGame::getMinScore(int a, int maxs)
{
    if (a == 0)
    {
        return finalScore();
    }

    QVector<Step *> steps;
    getAllarea(steps);

    double minScore = 10000;

    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        int score = getMaxScore(a - 1, minScore);
        backfakemove(step);
        delete step;

        //剪枝
        if (score <= maxs)
        {
            while (steps.count())
            {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if (score < minScore)
        {
            minScore = score;
        }
    }
    return minScore;
}

//己方棋子得分最高
int singleGame::getMaxScore(int a, int mins)
{
    if (a == 0)
    {
        return finalScore();
    }

    QVector<Step *> steps;
    getAllarea(steps);

    double maxScore = -10000;

    while (steps.count())
    {
        Step *step = steps.back();
        steps.removeLast();

        fakemove(step);
        double score = getMinScore(a - 1, maxScore);
        backfakemove(step);
        delete step;

        //剪枝
        if (score >= mins)
        {
            while (steps.count())
            {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if (score > maxScore)
        {
            maxScore = score;
        }
    }
    return maxScore;
}

//计算得分
int singleGame::finalScore()
{

    int rSum = 0;
    int bSum = 0;

    //将士卒炮马相車
    static int chessScore[] = {10000, 2, 1, 5, 6, 2, 10, 10000, 2, 1, 5, 6, 2, 10};

    for (int i = 0; i < 16; i++)
    {
        if (_s[i]._dead)
            continue;
        bSum += chessScore[_s[i]._type];
    }

    for (int i = 16; i < 32; i++)
    {
        if (_s[i]._dead)
            continue;
        rSum += chessScore[_s[i]._type];
    }

    return bSum - rSum;
}
