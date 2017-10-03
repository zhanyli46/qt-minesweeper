#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton : public QPushButton
{
    Q_OBJECT

public:
    MineButton(QWidget *parent = 0);
    ~MineButton();

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void leftClicked();
    void rightClicked();
};

#endif // MINEBUTTON_H
