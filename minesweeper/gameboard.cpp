#include "gameboard.h"
#include "ui_gameboard.h"

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    lv = EASY;
    // setup user interface
    h_offset= 12;
    top_offset = 24;
    bottom_offset = 12;
    dist_offset = 10;

    timer = new GameTimer(this);
    restart = new QPushButton(this);
    counter = new QLCDNumber(this);
    mz = new Minezone(this, lv);
    timer->resize(83, 30);
    restart->resize(30, 30);
    counter->resize(83, 30);
    mz->resize(216, 216);

    timer->move(h_offset, top_offset);
    restart->move(timer->pos().x() + timer->size().width() + dist_offset, top_offset);
    counter->move(restart->pos().x() + restart->size().width() + dist_offset, top_offset);
    mz->move(h_offset, timer->pos().y() + timer->size().height() + dist_offset);
    resize(h_offset * 2 + mz->size().width(), top_offset + bottom_offset + mz->size().height() + dist_offset + timer->size().height());

    connect(mz, SIGNAL(gameStart()), timer, SLOT(start()));
    connect(mz, SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(restart, SIGNAL(clicked(bool)), this, SLOT(restartGame()));

    setMinimumHeight(height());
    setMaximumHeight(height());
    setMinimumWidth(width());
    setMaximumWidth(width());
}

Gameboard::~Gameboard()
{
    delete ui;
    delete mz;
}

void Gameboard::endGame()
{
    timer->stop();
    mz->ignoreInputs();
    mz->showAllMines();
}

void Gameboard::restartGame()
{
    timer->reset();
    mz->resetZone(lv);
}
