#include "minebutton.h"

MineButton::MineButton(QWidget *parent)
    : QPushButton(parent),
      flag(false)
{
}

MineButton::~MineButton()
{
}

void MineButton::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::RightButton)
        emit rightClicked();
    else
        emit leftClicked();
}
