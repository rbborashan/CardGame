#include "cardmove.h"
#include "card.h"
#include "pile.h"

QStack<CardMove*> CardMove::undostack;

/* Constructor records a move in the undo stack. */
CardMove::CardMove(Card* _card, Pile* _from, Pile* _to)
    :card(_card), from(_from), to(_to), count(0)
{
    wasFaceUp = _card->Under()?_card->Under()->Faceup():false;
    undostack.push(this);
}

CardMove::CardMove(int _count) : count(_count) {undostack.push(this);}

/* Undoes the last move that was made and restores the previous
 * condition of the game before the move. */
void CardMove::UndoMove()
{
    if (undostack.empty()) return;

    CardMove* undo = undostack.pop();

    int n = undo->count;

    do
    {
        if(n)
        {
            delete undo;
            undo = undostack.pop();
        }

        if (undo->from->Top() && undo->from->Top()->Faceup() != undo->wasFaceUp)
            undo->from->Top()->Flip();

        undo->from->AcceptCards(undo->card, true, false);

        if (undo->from->Type() == DEAL) undo->card->Faceup(false);
        if (undo->from->Type() == DEALT && n % 3 == 0) undo->card->AlignWithPile();
    } while (--n > 0);

    delete undo;
}

/* Undoes all card moves since the initial deal. */
void CardMove::UndoAllMove()
{
    while (!undostack.isEmpty())
        UndoMove();
}

/* Empties the undo stack */
void CardMove::Clear()
{
    int n = undostack.size();

    while (n-- > 0){
        undostack.pop();
    }
}
