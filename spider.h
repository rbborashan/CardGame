#ifndef SPIDER_H
#define SPIDER_H

#include "game.h"

class Pile;

class Spider : public Game
{
    Pile* field[10];
    Pile* stock[5];
    Pile* playOff[8];
    int topStockPile; // index

public:
    Spider(QWidget*);

    bool okToDeal();

    void ReDeal();
    void OnStockClick(Card*);
};

#endif // SPIDER_H
