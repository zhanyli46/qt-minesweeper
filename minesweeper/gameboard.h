#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include "minezone.h"

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
    int zone_height;
    int zone_width;
    Difficulty lv;

private slots:
    void gameOver();
};

#endif // GAMEBOARD_H
