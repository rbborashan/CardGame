#include "freecell.h"
#include "pile.h"
#include "card.h"

Freecell::Freecell(QWidget* parent) : Game(parent) {}

/* Returns the number of free moves based on the number
 * of empty piles on the entire game board. */
int Freecell::FreeMoves()
{
    int f = 0;
    int n = 0;

    for (int i = 0; i  <  4; i++) f += freeCell[i]->Empty();

    for (int i = 0; i  <  8; i++) n += field[i]->Empty();

    int freemoves = (f + 1)<<n;

    return freemoves;
}

/*  Implementation of pure virtual function in Game class.
 *  Deals a deck of cards for freecell, instantiates piles,
 *  and adds rules to them. */
void Freecell::ReDeal()
{
    Clear();
    Card* Deck[52];
    for (int i = 0; i  <  52; i++)
    {
        Deck[i] = new Card(i, parent);
        Deck[i]->Faceup(true);
        Deck[i]->move(360,420);
    }

    Shuffle(Deck, 52);

    for (int i = 0; i  <  4; i++)
        foundation[i] = new PileFoundation(360 + 80 * i, 10, 0, 0, parent);

    foundation[0]->AddDropRules(4,
                             new RuleStackSameSuit,
                             new RuleStackPlusOne,
                             new RuleBaseAce,
                             new RuleMoveOneAtATime);

    foundation[0]->AddDragRules(1, new RuleMoveNone);

    for (int i = 0; i < 4; i++)
        freeCell[i] = new PileFreeCell(20 + 80 * i, 10, 0, 0, parent);

    freeCell[0]->AddDropRules(1, new RuleNoStack);

    for (int i=0; i < 8; i++)
        field[i] = new PileField(20 + 82 * i, 120, 0, 18, parent);

    field[0]->AddDropRules(3, new RuleStackAlternateColor,
                           new RuleStackLengthLimited,
                           new RuleStackMinusOne);

    field[0]->AddDragRules(3,
                           new RuleMoveLenghtLimited,
                           new RuleMoveAltColor,
                           new RuleMoveSeqDecreasing);

    for (int i = 0; i < 52; i++)
        Deck[i]->Move(field[i%8]);
}

/* Implementation of virtual function in the Game class.
 * Moves a card from a field pile to the first free cell
 * available (if any). */
void Freecell::OnFieldClick(Card* card)
{
    if(card)
    {
        for (int i = 0; i < 4; i++)
        {
            if (!freeCell[i]->Top())
            {
                freeCell[i]->AcceptCards(card);
                break;
            }
        }
    }
}

/* Implementation of virtual function in the Game class.
 * Plays a card off to the foundation pile from the free
 * cell pile when clicked. */
void Freecell::OnFreeCellClick(Card* card) {if (card) PlayOff(card);}

/* Implementation of virtual function in the Game class.
 * Plays a card off to the foundation pile from the field
 * when double clicked. */
void Freecell::OnFieldDoubleClick(Card* card) {if (card) PlayOff(card);}

