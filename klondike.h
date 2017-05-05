#ifndef KLONDIKE_H
#define KLONDIKE_H

#include <QWidget>

#include "game.h"

class Pile;

class Klondike : public Game
{
    // Card piles for a Klondike game
    Pile* stock;
    Pile* dealt;
    Pile* foundation[4];
    Pile* field[7];

public:
    Klondike(QWidget*);

    void ReDeal();
    void DealAction();
    void OnFieldClick(Card*);
    void OnStockClick(Card*);
    void OnDealtClick(Card*);
};

#endif // KLONDIKE_H
