#ifndef MINEZONE_H
#define MINEZONE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include "minebutton.h"

const int OFFSET_FROM_TOP = 60;
const int TILE_SIZE = 24;

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

enum Zonestatus {
    EMPTY = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    MINE,
    PRESSED
};

class Minezone : public QWidget
{
    Q_OBJECT

public:
    Minezone(QWidget *parent = 0, Difficulty lv = EASY);
    ~Minezone();
    void print();
    int getHeight() { return zone_height; }
    int getWidth() { return zone_width; }
    void acceptInputs();
    void ignoreInputs();
    void showAllMines();
    void resetZone(Difficulty lv);
    int getNumMines();

private:
    void setLevel(Difficulty lv);
    void createZone();
    void destroyZone();
    inline void mineIdToRC(int id, int *r, int *c);
    int numMinesAround(int r, int c);
    void generateMines(int r, int c);
    void generateHintTiles();
    void expandZone(int r, int c);

    int zone_height;
    int zone_width;
    int n_rows;
    int n_cols;
    int n_mines;
    bool firstClick;
    int numTileRemained;
    Zonestatus **zone;
    MineButton ***mine_btns;
    QSignalMapper *leftMapper;
    QSignalMapper *rightMapper;

private slots:
    void onLeftMouseClick(int btn_id);
    void onRightMouseClick(int btn_id);

signals:
    void gameStart();
    void gameWon();
    void gameOver();
    void label();
    void unlabel();

};

#endif // MINEZONE_H
