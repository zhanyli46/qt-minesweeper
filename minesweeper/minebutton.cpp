#include "minebutton.h"
#include <iostream>

MineButton::MineButton(QWidget *parent)
    : QPushButton(parent)
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
