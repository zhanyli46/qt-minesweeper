#ifndef TIMER_H
#define TIMER_H

#include <QLCDNumber>
#include <QTime>
#include <QTimer>

class GameTimer : public QLCDNumber
{
    Q_OBJECT

public:
    GameTimer(QWidget *parent = 0);
    ~GameTimer();
    void stop();
    void reset();

private:
    QTimer *timer;
    QTime startTime;

private slots:
    void start();
    void showTime();
};

#endif // TIMER_H
