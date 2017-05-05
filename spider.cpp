#include "card.h"
#include "pile.h"
#include "spider.h"

Spider::Spider(QWidget* parent) :Game(parent) {}

/* Implementation of the pure virtual method in the Game class.
 * Sets up the piles, adds rules to them, and deals a deck of
 * 104 Spades from Ace to King. */
void Spider::ReDeal()
{
    Card* Deck[104];
    topStockPile = 4;

    Clear();

    int minimum = 52 - SUIT_SIZE;
    int value = minimum;

    for (int i = 0; i < 104; i++)
    {
        Deck[i] = new Card(value, parent);

        value++;

        if (value == 52)
                value = minimum;
    }

    Shuffle(Deck, 104);

    for(int i = 0; i < 8; i++)
    {
        playOff[i] = new PileFoundation(20 + 17 * i, 550, 0, 0, parent);
    }

    playOff[0]->AddDragRules(1, new RuleMoveNone);
    playOff[0]->AddDropRules(1, new RuleStack13);

    for(int i = 0; i < 10; i++)
    {
        field[i] = new PileField(20 + 82 * i, 20, 0, 18, parent);
    }

    field[0]->AddDropRules(1, new RuleStackMinusOne);
    field[0]->AddDragRules(1, new RuleMoveSeqDecreasing);

    for(int i = 0; i < 5; i++)
    {
        stock[i] = new PileStock((20 + 17 * i) + 670, 550, 0, 0, parent);
    }

    stock[0]->AddDropRules(1, new RuleStackNone);
    stock[0]->AddDragRules(1, new RuleMoveNone);

    // Deal to first four field piles
    int j = 0;
    for (int i = 0; i < 4; i++)
        for(int k = 0; k < 6; k++)
        {
            if (k == 5)
                Deck[j]->Faceup(true);
            Deck[j++]->Move(field[i]);
        }

    // Deal to last six field piles
    for (int i = 4; i < 10; i++)
        for(int k = 0; k < 5; k++)
        {
            if (k == 4)
                Deck[j]->Faceup(true);
            Deck[j++]->Move(field[i]);
        }

    // Split remaining cards among the five stock piles
    for (int i = 0; i < 5; i++)
        for (int k = 0; k < 10; k++)
            Deck[j++]->Move(stock[i]);
}

/* Checks if there are any empty cells
 * on the field. */
bool Spider::okToDeal()
{
    for(int i = 0; i < 10; i++)
    {
        if (!field[i]->Top())
            return false;
    }

    return true;
}

/* Deals ten cards to the field (one per pile) from
 * the top stock pile. Only deals if there are no empty
 * cells on the field. */
void Spider::OnStockClick(Card* card)
{
    if (card && okToDeal())
    {
        for(int i = 0; i < 10; i++)
        {
            if (i == 0)
               stock[topStockPile]->Top()->Faceup(true);

            stock[topStockPile]->Top()->Move(field[i]);
        }

        --topStockPile;
    }
}
