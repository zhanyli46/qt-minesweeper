#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include "minezone.h"

enum Level {
    EASY,
    MEDIUM,
    HARD
};

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
    Minezone *mz;

private slots:
    void gameOver();
};

#endif // GAMEBOARD_H
