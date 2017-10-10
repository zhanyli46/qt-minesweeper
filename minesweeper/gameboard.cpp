#include "gameboard.h"
#include "ui_gameboard.h"

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    lv = EASY;
    mz = new Minezone(this, MEDIUM);
    zone_height = mz->getHeight();
    zone_width = mz->getWidth();
    mz->setGeometry(10, 10, zone_height, zone_width);
    this->setGeometry(400, 400, zone_height + 100, zone_width + 100);
    connect(mz, SIGNAL(sigGameOver()), this, SLOT(gameOver()));

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
