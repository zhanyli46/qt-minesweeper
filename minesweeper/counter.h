#ifndef COUNTER_H
#define COUNTER_H

#include <QLCDNumber>

class MineCounter : public QLCDNumber
{
    Q_OBJECT

public:
    MineCounter(QWidget *parent = 0, int n = 0);
    ~MineCounter();
    void setValue(int val);
private:
    int val;

public slots:
    void plusOne();
    void minusOne();

};

#endif // COUNTER_H
