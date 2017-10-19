#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include "minezone.h"
#include "timer.h"
#include "counter.h"

namespace Ui {
class Gameboard;
}

class Gameboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gameboard(QWidget *parent = 0);
    ~Gameboard();

private:
    Ui::Gameboard *ui;
    GameTimer *timer;
    QPushButton *restart;
    MineCounter *counter;
    Minezone *mz;
    Difficulty lv;
    int h_offset;
    int top_offset;
    int bottom_offset;
    int dist_offset;

private slots:
    void winGame();
    void endGame();
    void restartGame();
};

#endif // GAMEBOARD_H
