#include "rule.h"
#include "pile.h"
#include "card.h"
#include "gameboard.h"

extern GameBoard *MainApp;
extern Game *game;

/* Rule definitions. Implementations of the pure virtual Enforce
 * method of the Rule class by its children. */

bool RuleBaseNone::Enforce(Pile*, Card*)
{
    return false;
}

bool RuleBaseAce::Enforce(Pile* pile, Card* card)
{
    return !pile->Empty() || card->Pip() == ACE;
}

bool RuleBaseKing::Enforce(Pile* pile, Card* card)
{
    return !pile->Empty() || card->Pip()==KING;
}

bool RuleNoStack::Enforce(Pile* pile, Card* card)
{
    return pile->Empty() && !card->Over();
}

bool RuleStackSameSuit::Enforce(Pile* pile, Card* card)
{
    return pile->Empty() || card->Suit() == pile->Top()->Suit();
}

bool RuleStackAlternateColor::Enforce(Pile* pile, Card* card)
{
    return pile->Empty() || card->Color() != pile->Top()->Color();
}

bool RuleStackMinusOne::Enforce(Pile* pile, Card* card)
{
    return pile->Empty() || pile->Top()->Pip() - card->Pip() == 1;
}

bool RuleStackPlusOne::Enforce(Pile* pile, Card* card)
{
    return pile->Empty() || card->Pip() - pile->Top()->Pip() == 1;
}

bool RuleStackAny::Enforce(Pile*, Card*)
{
    return true;
}

bool RuleStackOneAtATime::Enforce(Pile*, Card* card)
{
    return card->Over() == NULL;
}

bool RuleStackNone::Enforce(Pile*, Card*)
{
    return false;
}

bool RuleStack13::Enforce(Pile* pile, Card* card)
{
    if (pile->Top())
        return false;

    Card* temp = card;
    bool ok = true;
    int value = card->Pip();
    suits suit = card->Suit();

    while (ok &&
            (ok = (temp->Pip() == value &&
                   temp->Suit() == suit))
            && value < KING)
    {
        value = (value + 1);
        temp = temp->Under();
        ok = temp;
    }

    return ok;
}

bool RuleStackLengthLimited::Enforce(Pile* pile, Card* card)
{
    int stack_size = card->StackSize();
    int freemoves = game->FreeMoves();
    freemoves>>= pile->Empty()?1:0;
    return stack_size <= freemoves;
}

bool RuleMoveSameSuit::Enforce(Pile*, Card* card)
{
    bool ok = true;
    while(ok && card->Over())
    {
        ok = card->Suit() == card->Over()->Suit();
        card = card->Over();
    }
    return ok;
}

bool RuleMoveAltColor::Enforce(Pile*, Card* card)
{
    bool ok = true;
    while(ok && card->Over())
    {
        ok = card->Color() != card->Over()->Color();
        card = card->Over();
    }
    return ok;
}

bool RuleMoveSeqDecreasing::Enforce(Pile*, Card* card)
{
    bool ok = true;
    while (ok && card->Over())
    {
        ok = 1 == card->Pip() - card->Over()->Pip();
        card = card->Over();
    }
    return ok;
}


bool RuleMoveSeqIncreasing::Enforce(Pile*, Card* card)
{
    bool ok = true;
    while(ok && card->Over())
    {
        ok= 1 == card->Over()->Pip()-card->Pip();
        card = card->Over();
    }
    return ok;
}


bool RuleMoveLenghtLimited::Enforce(Pile*, Card* card)
{
    return card->StackSize() <= game->FreeMoves();
}


bool RuleMoveNone::Enforce(Pile*, Card*)
{
    return false;
}


bool RuleMoveOneAtATime::Enforce(Pile*, Card* card)
{
    return !card->Over();
}
