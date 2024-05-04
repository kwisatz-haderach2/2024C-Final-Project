#ifndef START_H
#define START_H
#include"Board.h"
#include"singlegame.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class start;
}
QT_END_NAMESPACE

class start : public QMainWindow
{
    Q_OBJECT

public:
    start(QWidget *parent = nullptr);
    ~start();

private slots:

    void on_pushButton_ManMan_clicked();

    void on_pushButton_ManMachine_clicked();

private:
    Ui::start *ui;

    Board *b=new Board;

    singleGame *c=new singleGame ;

};
#endif // START_H




