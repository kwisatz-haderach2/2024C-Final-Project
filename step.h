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
    int rowfrom;
    int colfrom;
    int rowto;
    int colto;

signals:
public slots:
};
#endif
