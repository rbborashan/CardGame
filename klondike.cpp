#include "card.h"
#include "pile.h"
#include "game.h"
#include "klondike.h"
#include "gameboard.h"
#include "cardmove.h"

Klondike::Klondike(QWidget* parent) :Game(parent) {}

/* Implementation of pure virtual function in the Game class.
 * Deals a deck of cards, instantiates piles, and adds rules
 * to them. */
void Klondike::ReDeal()
{
    Card* Deck[52];

    Clear();

    for(int i = 0; i < 52; i++)
        Deck[i] = new Card(i, parent);

    Shuffle(Deck, 52);

    for(int i = 0; i < 4; i++)
        foundation[i] = new PileFoundation(266 + 82 * i, 10, 0, 0, parent);

    foundation[0]->AddDropRules(4,
                                new RuleStackSameSuit(),
                                new RuleStackPlusOne(),
                                new RuleBaseAce(),
                                new RuleMoveOneAtATime());

    foundation[0]->AddDragRules(0);

    for(int i = 0; i < 7; i++)
        field[i] = new PileField(20 + 82 * i, 120, 0, 18, parent);

    field[0]->AddDropRules(3,
                           new RuleStackAlternateColor(),
                           new RuleBaseKing(),
                           new RuleStackMinusOne());

    field[0]->AddDragRules(2,
                           new RuleMoveSeqDecreasing(),
                           new RuleMoveAltColor());

    stock = new PileStock(20, 10, 0, 0, parent);

    stock->AddDropRules(2,
                       new RuleBaseNone(),
                       new RuleNoStack());

    stock->AddDragRules(1, new RuleMoveNone());

    dealt = new PileDealt(100, 10, 16, 0, parent);

    dealt->AddDropRules(2,
                        new RuleBaseNone(),
                        new RuleNoStack());

    dealt->AddDragRules(1,new RuleMoveOneAtATime());

    int i = 0;
    for(int pass = 0; pass < 7; pass++)
        for(int pile = pass; pile < 7; pile++)
        {
            if(pass == pile)
                Deck[i]->Flip();
            Deck[i++]->Move(field[pile]);
        }

    while(i < 52)
        Deck[i++]->Move(stock);
}

/* Deals three cards at a time from the deck,
 * unique to the Klondike game. */
void Klondike::DealAction()
{
    Pile* pile = stock;
    int n = 0;

    if (stock->Top())
    {
        Card* card = stock->Top();

        card->Faceup(true);
        dealt->AcceptCards(card, true, true);
        n++;
        card->AlignWithPile();


        if (stock->Top())
        {
            dealt->AcceptCards(stock->Top(), true, true);
            n++;
        }

        if (stock->Top())
        {
            dealt->AcceptCards(stock->Top(), false, true);
            n++;
        }
    }

    else
    {
        while(dealt->Top())
        {
            dealt->Top()->Faceup(false);
            pile->AcceptCards(dealt->Top(), false, true);
            n++;
        }
    }

    if (n)
        new CardMove(n);
}

/* Plays a card off from the field to the foundation pile when
 * it is clicked. */
void Klondike::OnFieldClick(Card* card)
{
    if (card)
        PlayOff(card);
}

/* Deals three cards when the stock pile is clicked. */
void Klondike::OnStockClick(Card*) {DealAction();}

/* Plays off a card from the dealt pile to the
 * foundation when it is clicked. */
void Klondike::OnDealtClick(Card* card)
{
    if (card)
        PlayOff(card);
}
