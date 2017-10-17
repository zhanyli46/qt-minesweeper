#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "minezone.h"
#include "timer.h"

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
    QLCDNumber *counter;
    Minezone *mz;
    int zone_height;
    int zone_width;
    Difficulty lv;

private slots:
    void gameOver();
};

#endif // GAMEBOARD_H
