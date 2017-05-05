#ifndef FREECELL_H
#define FREECELL_H

#include <QWidget>

#include "game.h"

class Pile;

class Freecell : public Game
{
    // Card piles for a freecell game
    Pile* field[8];
    Pile* freeCell[4];
    Pile* foundation[4];

public:
    Freecell(QWidget*);

    int FreeMoves();

    void ReDeal();
    void DealAction();
    void OnFieldClick(Card*);
    void OnFreeCellClick(Card*);
    void OnFieldDoubleClick(Card*);
};

#endif // FREECELL_H
