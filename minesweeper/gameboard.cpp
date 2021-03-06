#include "gameboard.h"
#include "ui_gameboard.h"
#include <QIcon>
#include <QSize>
#include <QPixmap>

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    lv = EASY;
    // setup border offset
    h_offset= 12;
    top_offset = 24;
    bottom_offset = 12;
    dist_offset = 10;

    // initialize components
    timer = new GameTimer(this);
    restart = new QPushButton(this);
    mz = new Minezone(this, lv);
    counter = new MineCounter(this, mz->getNumMines());
    timer->resize(83, 30);
    restart->resize(30, 30);
    counter->resize(83, 30);
    mz->resize(mz->getHeight(), mz->getWidth());

    // set icon for the restart button
    QPixmap pm(":/img/restart.png");
    QIcon icon(pm);
    restart->setIcon(icon);
    restart->setIconSize(QSize(18, 18));

    // set component location
    timer->move(h_offset, top_offset);
    restart->move(timer->pos().x() + timer->size().width() + dist_offset, top_offset);
    counter->move(restart->pos().x() + restart->size().width() + dist_offset, top_offset);
    mz->move(h_offset, timer->pos().y() + timer->size().height() + dist_offset);
    resize(h_offset * 2 + mz->size().width(), top_offset + bottom_offset + mz->size().height() + dist_offset + timer->size().height());

    // connect component signals and slots
    connect(mz, SIGNAL(gameStart()), timer, SLOT(start()));
    connect(mz, SIGNAL(gameWon()), this, SLOT(winGame()));
    connect(mz, SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(restart, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    connect(mz, SIGNAL(label()), counter, SLOT(minusOne()));
    connect(mz, SIGNAL(unlabel()), counter, SLOT(plusOne()));

    // disable resizing of main window
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

void Gameboard::winGame()
{
    timer->stop();
    mz->ignoreInputs();
    mz->showWinningMessage();
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
    mz->acceptInputs();
    counter->setValue(mz->getNumMines());
}
