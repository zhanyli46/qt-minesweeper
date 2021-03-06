#include "timer.h"

GameTimer::GameTimer(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    showTime();
}

GameTimer::~GameTimer()
{

}

void GameTimer::start()
{
    timer->start(1000);
    startTime = QTime::currentTime();
}

void GameTimer::stop()
{
    timer->stop();
}

void GameTimer::reset()
{
    startTime = QTime::currentTime();
    display(startTime.elapsed());
    stop();
}

void GameTimer::showTime()
{
    if (startTime.elapsed() % 1000 >= 500)
        display(startTime.elapsed() / 1000 + 1);
    else
        display(startTime.elapsed() / 1000);
}
