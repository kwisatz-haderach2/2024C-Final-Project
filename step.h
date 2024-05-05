#ifndef STEP_H
#define STEP_H
#include <QObject>

class Step : public QObject
{
    Q_OBJECT
public:
    Step(QObject *parent = nullptr);
    ~Step();

    int firstclicked;
    int secondclicked;
    //初始位置
    int rowfrom;
    int colfrom;
    //落子位置
    int rowto;
    int colto;

signals:
public slots:
};
#endif
