#ifndef CARDMOVE_H
#define CARDMOVE_H

#include <QStack>

class Pile;
class Card;

class CardMove
{
    static QStack <CardMove*> undostack;

    Card* card;
    Pile* from;
    Pile* to;

    int count;
    bool wasFaceUp;

public:
    CardMove(Card*, Pile*, Pile*);
    CardMove(int);

    static void UndoMove();
    static void UndoAllMove();
    static void Clear();
};

#endif // CARDMOVE_H
