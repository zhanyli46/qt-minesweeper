#include "gameboard.h"
#include "ui_gameboard.h"
#include <iostream>

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    lv = EASY;
    // setup user interface
    int h_offset= 12;
    int top_offset = 24;
    int bottom_offset = 12;
    int dist_offset = 10;

    timer = new GameTimer(this);
    restart = new QPushButton(this);
    counter = new QLCDNumber(this);
    mz = new Minezone(this, EASY);
    timer->resize(83, 30);
    restart->resize(30, 30);
    counter->resize(83, 30);
    mz->resize(216, 216);

    timer->move(h_offset, top_offset);
    restart->move(timer->pos().x() + timer->size().width() + dist_offset, top_offset);
    counter->move(restart->pos().x() + restart->size().width() + dist_offset, top_offset);
    mz->move(h_offset, timer->pos().y() + timer->size().height() + dist_offset);
    resize(h_offset * 2 + mz->size().width(), top_offset + bottom_offset + mz->size().height() + dist_offset + timer->size().height());

    connect(mz, SIGNAL(sigGameOver()), this, SLOT(gameOver()));

    setMinimumHeight(height());
    setMaximumHeight(height());
    setMinimumWidth(width());
    setMaximumWidth(width());
}

Gameboard::~Gameboard()
{
    delete ui;
}

void Gameboard::gameOver()
{
    mz->ignoreInputs();
    mz->showAllMines();
}
