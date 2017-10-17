#include "minezone.h"
#include <QtGlobal>
#include <QQueue>
#include <ctime>
#include <iostream>

Minezone::Minezone(QWidget *parent, Difficulty lv) :
    QWidget(parent)
{
    // setup level info
    setLevel(lv);
    zone_height = n_rows * TILE_SIZE;
    zone_width = n_cols * TILE_SIZE;
    qsrand(time(0));
    firstClick = true;

    // setup mapper for buttons
    leftMapper = new QSignalMapper(this);
    rightMapper = new QSignalMapper(this);

    // setup minezone and ui
    zone = new Zonestatus*[n_rows];
    mine_btns = new MineButton**[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        zone[i] = new Zonestatus[n_cols];
        mine_btns[i] = new MineButton*[n_cols];
        for (int j = 0; j < n_cols; j++)
        {
            zone[i][j] = EMPTY;
            mine_btns[i][j] = new MineButton(this);
            mine_btns[i][j]->setFixedSize(TILE_SIZE, TILE_SIZE);
            mine_btns[i][j]->setCheckable(true);
            mine_btns[i][j]->move(TILE_SIZE * i, TILE_SIZE * j);

            // assign id to each button to handle signal
            int btn_id = i * n_rows + j;
            connect(mine_btns[i][j], SIGNAL(leftClicked()), leftMapper, SLOT(map()));
            connect(mine_btns[i][j], SIGNAL(rightClicked()), rightMapper, SLOT(map()));
            leftMapper->setMapping(mine_btns[i][j], btn_id);
            rightMapper->setMapping(mine_btns[i][j], btn_id);
        }
    }

    // connect the mapper to handler function
    connect(leftMapper, SIGNAL(mapped(int)), this, SLOT(onLeftMouseClick(int)));
    connect(rightMapper, SIGNAL(mapped(int)), this, SLOT(onRightMouseClick(int)));

}

Minezone::~Minezone()
{
    for (int i = 0; i < n_rows; i++)
    {
        delete zone[i];
        for (int j = 0; j < n_cols; j++)
            delete mine_btns[i][j];
        delete mine_btns[i];
    }
    delete zone;
    delete mine_btns;
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

void Minezone::ignoreInputs()
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Minezone::showAllMines()
{
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            if (zone[i][j] == MINE && !mine_btns[i][j]->isFlagged()) {
                mine_btns[i][j]->setText("*");
                mine_btns[i][j]->setChecked(true);
            }
        }
    }
}

void Minezone::setLevel(Difficulty lv)
{
    if (lv == EASY) {
        n_rows = 9;
        n_cols = 9;
        n_mines = 10;
    } else if (lv == MEDIUM) {
        n_rows = 16;
        n_cols = 16;
        n_mines = 40;
    } else {
        n_rows = 30;
        n_cols = 16;
        n_mines = 99;
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

void Minezone::expandZone(int r, int c)
{
    QQueue<int> queue;
    queue.enqueue(r * n_rows + c);
    while (!queue.empty()) {
        int btn_id = queue.dequeue();
        int i, j;
        mineIdToRC(btn_id, &i, &j);
        MineButton *btn = mine_btns[i][j];
        Zonestatus btn_stat = zone[i][j];
        if (btn_stat == PRESSED || btn->isFlagged())
            continue;
        if (btn_stat == EMPTY) {
            if (i + 1 < n_rows)
                queue.enqueue((i + 1) * n_rows + j);
            if (j + 1 < n_cols)
                queue.enqueue(i * n_rows + (j + 1));
            if (i - 1 >= 0)
                queue.enqueue((i - 1) * n_rows + j);
            if (j - 1 >= 0)
                queue.enqueue(i * n_rows + (j - 1));
            btn->setChecked(true);
            zone[i][j] = PRESSED;
        } else if (btn_stat == MINE) {
            btn->setText("*");
            btn->setChecked(true);
            emit sigGameOver();
        } else {
            if (numMinesAround(i, j) == 0) {
                if (i + 1 < n_rows)
                    queue.enqueue((i + 1) * n_rows + j);
                if (j + 1 < n_cols)
                    queue.enqueue(i * n_rows + (j + 1));
                if (i - 1 >= 0)
                    queue.enqueue((i - 1) * n_rows + j);
                if (j - 1 >= 0)
                    queue.enqueue(i * n_rows + (j - 1));
                btn->setChecked(true);
            }
            btn->setText(QString::number(static_cast<int>(btn_stat)));
            btn->setChecked(true);
            zone[i][j] = PRESSED;
        }
    }
}

void Minezone::onLeftMouseClick(int btn_id)
{
    int r, c;
    mineIdToRC(btn_id, &r, &c);
    if (firstClick) {
        firstClick = false;
        generateMines(r, c);
        generateHintTiles();
    }
    expandZone(r, c);
}

void Minezone::onRightMouseClick(int btn_id)
{
    int r, c;
    mineIdToRC(btn_id, &r, &c);
    bool flagged = mine_btns[r][c]->isFlagged();
    bool pressed = zone[r][c] == PRESSED;
    if (pressed)
        return;
    if (flagged) {
        mine_btns[r][c]->setText("");
    } else {
        mine_btns[r][c]->setText("F");
    }
    mine_btns[r][c]->setFlagged(!flagged);
}
