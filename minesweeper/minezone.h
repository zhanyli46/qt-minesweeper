#ifndef MINEZONE_H
#define MINEZONE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>

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
    Minezone(QWidget *parent = 0);
    ~Minezone();
    void print();

private:
    inline void mineIdToRC(int id, int *r, int *c);
    int numMinesAround(int r, int c);
    void generateMines(int r, int c);
    void generateHintTiles();
    void expandZone(int r, int c);
    int n_rows;
    int n_cols;
    int n_mines;
    bool firstClick;
    Zonestatus **zone;
    QPushButton ***mine_btns;
    QGridLayout *zone_grid;
    QSignalMapper *mapper;

private slots:
    void mineButtonHandler(int btn_id);
};

#endif // MINEZONE_H
