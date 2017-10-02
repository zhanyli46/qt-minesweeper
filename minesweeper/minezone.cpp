#include "minezone.h"
#include <QtGlobal>
#include <ctime>
#include <iostream>

Minezone::Minezone(QWidget *parent) :
    QWidget(parent)
{
    // setup level info
    n_rows = 9;
    n_cols = 9;
    n_mines = 10;
    qsrand(time(0));
    firstClick = true;

    // setup mapper for buttons
    mapper = new QSignalMapper(this);

    // setup minezone and ui
    zone = new Zonestatus*[n_rows];
    zone_grid = new QGridLayout(this);
    mine_btns = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        zone[i] = new Zonestatus[n_cols];
        mine_btns[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; j++)
        {
            zone[i][j] = EMPTY;
            mine_btns[i][j] = new QPushButton(this);
            mine_btns[i][j]->setFixedSize(24, 24);
            zone_grid->addWidget(mine_btns[i][j], i, j);

            // assign id to each button to handle signal
            int btn_id = i * n_rows + j;
            connect(mine_btns[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(mine_btns[i][j], btn_id);
        }
    }

    // connect the mapper to handler function
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(mineButtonHandler(int)));
}

Minezone::~Minezone()
{
//    Zonestatus **zone;
//    QPushButton ***mine_btns;
//    QGridLayout *zone_grid;
    for (int i = 0; i < n_rows; i++)
    {
        delete zone[i];
        for (int j = 0; j < n_cols; j++)
            delete mine_btns[i][j];
        delete mine_btns[i];
    }
    delete zone;
    delete mine_btns;
    delete zone_grid;
}

void Minezone::print()
{
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
            std::cerr << zone[i][j] << " ";
        std::cerr << "\n";
    }
}

void Minezone::generateMines(int r1, int c1)
{
    int i = 0;
    while (i < n_mines)
    {
        int mine_id = qrand() % (n_rows * n_cols);
        // convert mine_id to row and col
        int r = 0, c = 0;
        mineIdToRC(mine_id, &r, &c);
        int lr = r1 - 1 >= 0 ? r1 - 1 : r1;
        int hr = r1 + 1 < n_rows ? r1 + 1 : r1;
        int lc = c1 - 1 >= 0 ? c1 - 1 : c1;
        int hc = c1 + 1 < n_cols ? c1 + 1 : c1;
        if (lr <= r && r <= hr && lc <= c && c <= hc)
            continue;
        if (zone[r][c] == EMPTY) {
            zone[r][c] = MINE;
            i += 1;
        }
    }
}

void Minezone::generateHintTiles()
{
    // generate hint tiles surrounding mines
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            if (zone[i][j] == MINE)
                continue;
            zone[i][j] = static_cast<Zonestatus>(numMinesAround(i, j));
        }
    }
}

inline void Minezone::mineIdToRC(int id, int *r, int *c)
{
    *r = id / n_rows;
    *c = id % n_rows;
}

int Minezone::numMinesAround(int r, int c)
{
    int sum = 0;
    int lr = r - 1 >= 0 ? r - 1 : r;
    int hr = r + 1 < n_rows ? r + 1 : r;
    int lc = c - 1 >= 0 ? c - 1 : c;
    int hc = c + 1 < n_cols ? c + 1 : c;

    for (int i = lr; i <= hr; i++)
        for (int j = lc; j <= hc; j++)
            if (zone[i][j] == MINE)
                sum += 1;

    if (zone[r][c] == MINE)
        return sum - 1;
    return sum;
}


void Minezone::mineButtonHandler(int btn_id)
{
    if (firstClick)
    {
        firstClick = false;
        int r1, c1;
        mineIdToRC(btn_id, &r1, &c1);
        generateMines(r1, c1);
        generateHintTiles();
    }
    print();
}
