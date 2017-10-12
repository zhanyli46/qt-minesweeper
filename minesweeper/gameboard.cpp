#include "gameboard.h"
#include "ui_gameboard.h"

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    lv = EASY;
    // setup user interface
    central = new QWidget(this);
    layout = new QGridLayout(central);
    timer = new GameTimer(central);
    restart = new QPushButton(central);
    mineCount = new QLCDNumber(central);
    mz = new Minezone(this, EASY);
    layout->addWidget(timer, 0, 0);
    layout->addWidget(restart, 0, 1);
    layout->addWidget(mineCount, 0, 2);
    layout->addWidget(mz, 1, 0);
    setCentralWidget(central);




//    this->setGeometry(400, 400, zone_height + 100, zone_width + 100);
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
