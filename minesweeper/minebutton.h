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
    bool isFlagged() { return flag; }
    void setFlagged(bool b) { flag = b; }

private:
    bool flag;

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void leftClicked();
    void rightClicked();
};

#endif // MINEBUTTON_H
