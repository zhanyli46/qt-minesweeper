#include "counter.h"

MineCounter::MineCounter(QWidget *parent, int n)
    : QLCDNumber(parent),
      val(n)
{
    display(val);
}

MineCounter::~MineCounter()
{
}

void MineCounter::setValue(int val)
{
    this->val = val;
    display(val);
}

void MineCounter::plusOne()
{
    val += 1;
    display(val);
}

void MineCounter::minusOne()
{
    val -= 1;
    display(val);
}
