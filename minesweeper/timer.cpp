#include "timer.h"

GameTimer::GameTimer(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
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

void GameTimer::showTime()
{
    display(startTime.elapsed() / 1000);
}
