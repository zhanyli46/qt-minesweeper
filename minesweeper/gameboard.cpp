#include "gameboard.h"
#include "ui_gameboard.h"

Gameboard::Gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gameboard)
{
    ui->setupUi(this);
    mz = new Minezone(this);
    mz->setGeometry(10, 10, 216, 216);
    mz->print();
}

Gameboard::~Gameboard()
{
    delete ui;
}
