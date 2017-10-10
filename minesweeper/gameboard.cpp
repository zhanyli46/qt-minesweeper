#include "gameboard.h"
#include "ui_gameboard.h"

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    // setup mine zone and ui
    mz = new Minezone(this);
    mz->setGeometry(10, 10, 216, 216);
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
